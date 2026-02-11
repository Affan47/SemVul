HPL_slamc5
(
   const int                  BETA,
   const int                  P,
   const int                  EMIN,
   const int                  IEEE,
   int                        * EMAX,
   float                     * RMAX
)
#else
static void HPL_slamc5( BETA, P, EMIN, IEEE, EMAX, RMAX )


   const int                  BETA, EMIN, IEEE, P;
   int                        * EMAX;
   float                     * RMAX;
#endif
{


   float                     oldy=HPL_rzero, recbas, y, z;
   int                        exbits=1, expsum, i, lexp=1, nbits, try_,
                              uexp;


l_10:
   try_ = (int)( (unsigned int)(lexp) << 1 );
   if( try_ <= ( -EMIN ) ) { lexp = try_; exbits++; goto l_10; }

   if( lexp == -EMIN ) { uexp = lexp; } else { uexp = try_; exbits++; }


   if( ( uexp+EMIN ) > ( -lexp-EMIN ) )
   { expsum = (int)( (unsigned int)(lexp) << 1 ); }
   else
   { expsum = (int)( (unsigned int)(uexp) << 1 ); }


   *EMAX = expsum + EMIN - 1;


   nbits = 1 + exbits + P;

   if( ( nbits % 2 == 1 ) && ( BETA == 2 ) )
   {


      (*EMAX)--;
   }

   if( IEEE != 0 )
   {


      (*EMAX)--;
   }


   recbas = HPL_rone / (float)(BETA);
   z      = (float)(BETA) - HPL_rone;
   y      = HPL_rzero;

   for( i = 0; i < P; i++ )
   { z *= recbas; if( y < HPL_rone ) oldy = y; y = HPL_slamc3( y, z ); }

   if( y >= HPL_rone ) y = oldy;


   for( i = 0; i < *EMAX; i++ ) y = HPL_slamc3( y * BETA, HPL_rzero );

   *RMAX = y;


}
