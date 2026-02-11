mlsadf1(double x, double *b, int m, double a, int pd, double *d, VocoderSetup *vs)
{
   double v, out = 0.0, *pt, aa;
   register int i;

   aa = 1 - a*a;
   pt = &d[pd+1];

   for (i=pd; i>=1; i--) {
      d[i] = aa*pt[i-1] + a*d[i];
      pt[i] = d[i] * b[1];
      v = pt[i] * vs->ppade[i];
      x += (1 & i) ? v : -v;
      out += v;
   }

   pt[0] = x;
   out += x;

   return(out);
}
