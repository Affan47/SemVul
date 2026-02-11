cblas_daxpy
(
   const int                  N,
   const double               ALPHA,
   const double               * X,
   const int                  INCX,
   double                     * Y,
   const int                  INCY
)
{


   register const double      alpha = ALPHA;
   register double            x0, x1, x2, x3, y0, y1, y2, y3;
   double                     * StX;
   register int               i;
   int                        nu;
   const int                  incX2 = 2 * INCX, incY2 = 2 * INCY,
                              incX3 = 3 * INCX, incY3 = 3 * INCY,
                              incX4 = 4 * INCX, incY4 = 4 * INCY;


   if( ( N > 0 ) && ( alpha != ATL_dZERO ) )
   {
      if( ( nu = ( N >> 2 ) << 2 ) != 0 )
      {
         StX = (double *)X + nu * INCX;

         do
         {
            x0 = (*X);     y0 = (*Y);     x1 = X[INCX ]; y1 = Y[INCY ];
            x2 = X[incX2]; y2 = Y[incY2]; x3 = X[incX3]; y3 = Y[incY3];

            *Y       = y0 + alpha * x0; Y[INCY ] = y1 + alpha * x1;
            Y[incY2] = y2 + alpha * x2; Y[incY3] = y3 + alpha * x3;

            X  += incX4;
            Y  += incY4;

         } while( X != StX );
      }

      for( i = N - nu; i != 0; i-- )
      {
         x0  = (*X);
         y0  = (*Y);

         *Y  = y0 + alpha * x0;

         X  += INCX;
         Y  += INCY;
      }
   }


}
