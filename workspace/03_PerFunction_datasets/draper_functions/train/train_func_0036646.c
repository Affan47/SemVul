inside_wall(double *xs, int iwall)
{
  int dim = wallwhich[iwall] / 2;
  int side = wallwhich[iwall] % 2;

  if (side == 0 && xs[dim] < xwall[iwall]) return 1;
  if (side && xs[dim] > xwall[iwall]) return 1;
  return 0;
}
