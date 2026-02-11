HTS_mc2b(double *mc, double *b, int m, const double a)
{
   if (mc != b) {
      if (a != 0.0) {
         b[m] = mc[m];
         for (m--; m >= 0; m--)
            b[m] = mc[m] - a * b[m + 1];
      } else
         HTS_movem(mc, b, m + 1);
   } else if (a != 0.0)
      for (m--; m >= 0; m--)
         b[m] -= a * b[m + 1];
}
