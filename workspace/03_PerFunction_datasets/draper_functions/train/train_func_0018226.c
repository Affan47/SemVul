inside(double x, double y, double z)
{
  double a = hinv[0][0]*(x-xlo) + hinv[0][1]*(y-ylo) + hinv[0][2]*(z-zlo);
  double b = hinv[1][1]*(y-ylo) + hinv[1][2]*(z-zlo);
  double c = hinv[2][2]*(z-zlo);

  if (a >= 0.0 && a <= 1.0 && b >= 0.0 && b <= 1.0 && c >= 0.0 && c <= 1.0)
    return 1;
  return 0;
}
