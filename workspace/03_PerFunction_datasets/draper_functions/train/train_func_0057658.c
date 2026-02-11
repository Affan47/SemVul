HTS_gnorm(double *c1, double *c2, int m, const double g)
{
   double k;
   if (g != 0.0) {
      k = 1.0 + g * c1[0];
      for (; m >= 1; m--)
         c2[m] = c1[m] / k;
      c2[0] = pow(k, 1.0 / g);
   } else {
      HTS_movem(&c1[1], &c2[1], m);
      c2[0] = exp(c1[0]);
   }
}
