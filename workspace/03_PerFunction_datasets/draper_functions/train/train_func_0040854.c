spol(int n, double *v, int k)
{


  int l, ifault;
  double rn, dsum, dwsum;

  if (n < 1)
    return 1;
  ifault = 0;
  rn = n;
  dsum = 0.0;
  dwsum = 0.0;
  for (l = 1; l <= n; l++) {
    dsum = dsum + v[l];
    dwsum = dwsum + v[l] * (rn - 1.0 - 2.0 * (l - 1));
  }
  if ((((k % 2) == 0) && (dsum < 0.0)) || (((k % 2) == 1) && (dwsum < 0.0)))
    for (l = 1; l <= n; l++)
      v[l] = -v[l];

  return ifault;
}
