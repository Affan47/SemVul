c2ir (double *c, int nc, double *h, int leng)
{
   register int n, k, upl;
   double  d;

   h[0] = exp(c[0]);
   for (n=1; n<leng; n++) {
      d = 0;
      upl = (n>=nc) ? nc-1 : n;
      for (k=1; k<=upl; k++)
         d += k*c[k]*h[n-k];
      h[n] = d/n;
   }

   return;
}
