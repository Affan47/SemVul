test_matrix (void)
{
   double M[3][3] = { { 1., 3., 1. },
                      { 1., 1., 2. },
                      { 2., 3., 4. } };
   double comp[3][3] = { { 2., 9., -5. },
                         { 0., -2., 1. },
                         { -1., -3., 2. } };
   double eye[3][3] = { { 1., 0., 0. },
                        { 0., 1., 0. },
                        { 0., 0., 1. } };
   double det, inv[3][3], mmul[3][3];

   det = mat3_det( M );
   if (fabs(det+1.) > 1e-10) {
      fprintf( stderr, "Error with determinant, got %.3e expected -1.\n", det );
      return -1;
   }

   mat3_inv( inv, M );
   if (mat3_cmp( inv, comp ) != 0) {
      fprintf( stderr, "Error with matrix inversion!\n" );
      printf( "Got:\n" );
      mat3_print( inv );
      printf( "Expected:\n" );
      mat3_print( comp );
      return -1;
   }

   mat3_mul( mmul, M, inv );
   if (mat3_cmp( mmul, eye ) != 0) {
      fprintf( stderr, "Error with matrix multiplication!\n" );
      printf( "Got:\n" );
      mat3_print( mmul );
      printf( "Expected:\n" );
      mat3_print( eye );
      return -1;
   }

   return 0;
}
