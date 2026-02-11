test_solve (void)
{
   int i, j, k;
   double A[3][3], b[3], x[3], solved[3];


   rnd_init();

   for (i=0; i<10000; i++) {
      for (j=0; j<3; j++) {
         for (k=0; k<3; k++)
            A[j][k] = rnd_double();
         x[j] = rnd_double();
      }
      mat3_mul_vec( b, A, x );


      if (fabs(mat3_det(A)) < DQ_PRECISION)
         continue;


      mat3_solve( solved, A, b );
      if (vec3_cmp( solved, x )) {
         fprintf( stderr, "Failed to solve 3x3 system!\n" );
         printf( "Got:\n" );
         vec3_print( solved );
         printf( "Expected:\n" );
         vec3_print( x );
         return -1;
      }
   }

   return 0;
}
