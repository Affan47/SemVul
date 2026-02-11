test_extract (void)
{
   int i, j;
   dq_t Q, P;
   double R[3][3], d[3];
   double a[3];


   rnd_init();


   for (j=0; j<10000; j++) {

      for (i=0; i<3; i++) {
         a[i] = 2.*M_PI * rnd_double();
         d[i] = 10. * rnd_double() - 5.;
      }
      test_mat_rot( R, a[0], a[1], a[2] );
      dq_cr_homo( Q, R, d );


      dq_op_extract( R, d, Q );
      dq_cr_homo( P, R, d );

      if (dq_ch_cmp( Q, P ) != 0) {
         fprintf( stderr, "Failed dual quaternion extraction test!\n" );
         printf( "Q:\n" );
         dq_print_vert( Q );
         printf( "P:\n" );
         dq_print_vert( P );
         return -1;
      }
   }
   return 0;
}
