factor(int n, int **factors)
{
  int i,j,nyz;

  int m = 0;
  for (i = 1; i <= n; i++) {
    if (n % i) continue;
    nyz = n/i;
    for (j = 1; j <= nyz; j++) {
      if (nyz % j) continue;
      if (factors) {
        factors[m][0] = i;
        factors[m][1] = j;
        factors[m][2] = nyz/j;
      }
      m++;
    }
  }

  return m;
}
