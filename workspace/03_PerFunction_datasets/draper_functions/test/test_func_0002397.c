scale2d (double x[], double y[], int n, double xfact, double yfact)
{
  for (int i = 0; i < n; i++) {
    x[i] *= xfact;
    y[i] *= yfact;
  }
}
