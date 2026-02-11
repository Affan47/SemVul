lubksb(Real* B, int mini)
{
   REPORT


   Tracer tr("Crout(lubksb)");
   if (sing) Throw(SingularException(*this));
   int i, j, ii = nrows_val;


   for (i = 0; i < nrows_val; i++)
   {
      int ip = indx[i]; Real temp = B[ip]; B[ip] = B[i]; B[i] = temp;
      if (temp != 0.0) { ii = i; break; }
   }

   Real* bi; Real* ai;
   i = ii + 1;

   if (i < nrows_val)
   {
      bi = B + ii; ai = store + ii + i * nrows_val;
      for (;;)
      {
         int ip = indx[i]; Real sum = B[ip]; B[ip] = B[i];
         Real* aij = ai; Real* bj = bi; j = i - ii;
         while (j--) sum -= *aij++ * *bj++;
         B[i] = sum;
         if (++i == nrows_val) break;
         ai += nrows_val;
      }
   }

   ai = store + nrows_val * nrows_val;

   for (i = nrows_val - 1; i >= mini; i--)
   {
      Real* bj = B+i; ai -= nrows_val; Real* ajx = ai+i;
      Real sum = *bj; Real diag = *ajx;
      j = nrows_val - i; while(--j) sum -= *(++ajx) * *(++bj);
      B[i] = sum / diag;
   }
}
