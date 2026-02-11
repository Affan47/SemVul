RealFFT(const ColumnVector& U, ColumnVector& X, ColumnVector& Y)
{

   Tracer trace("RealFFT");
   REPORT
   const int n = U.Nrows();
   const int n2 = n / 2;
   if (n != 2 * n2)
      Throw(ProgramException("Vector length not multiple of 2", U));
   ColumnVector A(n2), B(n2);
   Real* a = A.Store(); Real* b = B.Store(); Real* u = U.Store(); int i = n2;
   while (i--) { *a++ = *u++; *b++ = *u++; }
   FFT(A,B,A,B);
   int n21 = n2 + 1;
   X.resize(n21); Y.resize(n21);
   i = n2 - 1;
   a = A.Store(); b = B.Store();
   Real* an = a + i; Real* bn = b + i;
   Real* x = X.Store(); Real* y = Y.Store();
   Real* xn = x + n2; Real* yn = y + n2;

   *x++ = *a + *b; *y++ = 0.0;
   *xn-- = *a++ - *b++; *yn-- = 0.0;

   int j = -1; i = n2/2;
   while (i--)
   {
      Real c,s; cossin(j--,n,c,s);
      Real am = *a - *an; Real ap = *a++ + *an--;
      Real bm = *b - *bn; Real bp = *b++ + *bn--;
      Real samcbp = s * am + c * bp; Real sbpcam = s * bp - c * am;
      *x++  =  0.5 * ( ap + samcbp); *y++  =  0.5 * ( bm + sbpcam);
      *xn-- =  0.5 * ( ap - samcbp); *yn-- =  0.5 * (-bm + sbpcam);
   }
}
