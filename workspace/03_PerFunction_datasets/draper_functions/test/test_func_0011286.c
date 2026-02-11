operator/(const GcPoint& p, int num)
{
  double tmp[MAX_DIMENSION];

  for (short i = 0; i < MAX_DIMENSION; i++)
    if ( num != 0 )
      tmp[i] = p.posit[i] / num;

  return GcPoint(tmp[X], tmp[Y], tmp[Z]);
}
