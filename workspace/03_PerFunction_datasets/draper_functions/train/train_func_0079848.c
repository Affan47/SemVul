dickmanrho (double alpha)
{
  if (alpha <= 3.)
     return rhoexact (alpha);
  if (alpha < tablemax)
    {
      int a = floor (alpha * invh);
      double rho1 = rhotable[a];
      double rho2 = (a + 1) < tablemax * invh ? rhotable[a + 1] : 0;
      return rho1 + (rho2 - rho1) * (alpha * invh - (double)a);
    }

  return 0.;
}
