embofs(double *xemb, double *xmoon)
{
  int i;
  for (i = 0; i <= 2; i++)
    xemb[i] -= xmoon[i] / (EARTH_MOON_MRAT + 1.0);
}
