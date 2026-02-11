test_movement (void)
{
   int i;
   double a, p[3], t[3], s[3], c[3], pf[3];
   dq_t P, R, T, RT, RTP, PF;


   a    = M_PI/2.;
   p[0] = 0.;
   p[1] = 0.;
   p[2] = 0.;
   s[0] = 1./M_SQRT2;
   s[1] = -1./M_SQRT2;
   s[2] = 0.;
   c[0] = 1.;
   c[1] = 0.;
   c[2] = 0.;
   t[0] = 1.;
   t[1] = 2.;
   t[2] = 3.;
   pf[0] = 0.5;
   pf[1] = 0.5;
   pf[2] = -1./M_SQRT2;
   for (i=0; i<3; i++)
      pf[i] = pf[i] + t[i];


   dq_cr_point( P, p );
   dq_cr_rotation( R, a, s, c );
   dq_cr_translation_vector( T, t );
   dq_op_mul( RT, T, R );
   dq_op_f4g( RTP, R, P );
   dq_op_f4g( RTP, RT, P );
   dq_cr_point( PF, pf );


   if (!dq_ch_unit( R )) {
      fprintf( stderr, "Rotation dual quaternion R is not a unit dual quaternion!\n");
      dq_print_vert( R );
      return 1;
   }


   if (dq_ch_cmp( PF, RTP ) != 0) {
      fprintf( stderr, "Rotation+Translation failed!\n" );
      printf( "Point:\n" );
      dq_print_vert( P );
      printf( "Rotation:\n" );
      dq_print_vert( R );
      printf( "Translation:\n" );
      dq_print_vert( T );
      printf( "Rotation+Translation:\n" );
      dq_print_vert( RT );
      printf( "Got:\n" );
      dq_print_vert( RTP );
      printf( "Expected:\n" );
      dq_print_vert( PF );
      return -1;
   }

   return 0;
}
