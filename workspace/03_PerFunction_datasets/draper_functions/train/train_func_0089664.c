MinDifference(deg1, deg2)
real deg1, deg2;
{
  real i;

  i = deg2 - deg1;
  if (RAbs(i) < rDegHalf)
    return i;
  return RSgn(i)*(RAbs(i) - rDegMax);
}
