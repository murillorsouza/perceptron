// Perceptron learning

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ISIZE 2
#define WSIZE ( ISIZE + 1 ) // weights + bias
#define LEARNING_RATE  0.01
#define ITERATIONS     200

typedef int ivector[ ISIZE ];
typedef float wvector[ WSIZE ];

wvector weights={0, 0, 0};

void initialize( void )
{
   // Seed the random number generator
   srand( time( NULL ) );

   // Initialize the weights with random values
   for ( int i = 0 ; i < WSIZE ; i++ ) 
   {
      weights[ i ] = ( ( float ) rand( ) / ( float ) RAND_MAX );
   }

   printf("\n");
   printf("Initial weights %f %f bias %f\n", weights[0], weights[1], weights[2]);
   printf("\n");
}

int feedforward( ivector inputs )
{
   int i;
   float sum = 0.0;

   // Calculate inputs * weights
   for ( i = 0 ; i < ISIZE ; i++ ) sum += weights[ i ] * ( float ) inputs[ i ];

   // Add in the bias
   sum += weights[ i ];

   // Activation function (1 if value >= 1.0).
   return ( sum >= 1.0 ) ? 1 : 0;
}

void train( void )
{
   int iterations = 0;
   int iteration_error = 0;
   int desired_output, output, error;

   // Train the boolean XOR set
   ivector test[4] = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };

   do 
   {
      iteration_error = 0.0;

      printf( "Iteration %d\n", iterations );

      for ( int i = 0 ; i < ( sizeof( test ) / sizeof( ivector ) ) ; i++ )
      {
         //desired_output = test[ i ][ 0 ] |= test[ i ][ 1 ];
         if (test[ i ][ 0 ] == test[ i ][ 1 ]) 
         {
            desired_output = 0;
         } 
         else 
         {
            desired_output = 1;
         }
         output = feedforward( test[ i ] );

         error = desired_output - output;

         printf("%d and %d = %d (%d)\n", test[i][0], test[i][1], output, desired_output );

         weights[ 0 ] += ( LEARNING_RATE * ( ( float ) error * ( float )test[ i ][ 0 ] ) );
         weights[ 1 ] += ( LEARNING_RATE * ( ( float ) error * ( float )test[ i ][ 1 ] ) );
         weights[ 2 ] += ( LEARNING_RATE * ( float ) error );

            
         iteration_error += ( error * error );
         
         //printf("Partial weights %f %f bias %f\n", weights[0], weights[1], weights[2]);
         //printf( "Iteration error %d\n", iteration_error );
         //printf( "Error %d\n", error );
      }

      printf( "Iteration error %d\n", iteration_error );
      //printf( "Error %d\n", error );
      
      printf("Partial weights %f %f bias %f\n", weights[0], weights[1], weights[2]);
      //printf("\n");

   } while ( ( iteration_error > 0.0 ) && ( iterations++ < ITERATIONS ) );

   return;
}


int main( void )
{
   initialize( );

   train( );

   printf("Final weights %f %f bias %f\n", weights[0], weights[1], weights[2]);

   return 0;
}
