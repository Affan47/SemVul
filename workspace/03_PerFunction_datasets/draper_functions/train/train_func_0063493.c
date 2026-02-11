ATL_zdotc_sub(const int N, const TYPE *X, const int incX,
                   const TYPE *Y, const int incY, TYPE *dotc)
{
   int incx=incX, incy=incY;

   if (N > 0)
   {


      if (incX >= 0 && incY >= 0) goto L1;
      else if (incY < 0)
      {
         if (incX < 0)
         {
            incx = -incX;
            incy = -incY;
            X += ((N-1)SHIFT)*incX;
            Y += ((N-1)SHIFT)*incY;
         }
         else if (incX != 1 || incY == -1)
         {
            incy = -incY;
            Y += ((N-1)SHIFT)*incY;
            incx = -incX;
            X += ((N-1)SHIFT)*incX;
         }
      }
      else if (incX == -1 && incY != 1)
      {
         incx = 1;
         X -= ((N-1)SHIFT);
         incy = -incY;
         Y += ((N-1)SHIFT)*incY;
      }
      else if (!incX || !incY) return;
L1:

      ATL_zdotc_xp0yp0aXbX(N, X, incx, Y, incy, dotc);
   }
   else dotc[0] = dotc[1] = ATL_rzero;
}
