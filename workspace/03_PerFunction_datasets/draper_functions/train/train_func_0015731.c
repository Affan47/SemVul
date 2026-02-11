sort(int n, float *ra)
{
  int l,j,ir,i;
  float rra;

  if (n == 1)
      return;

  l=(n >> 1)+1;
  ir=n;
  for (;;) {
    if (l > 1) {
      --l;
      rra=ra[l-1];
    } else {
      rra=ra[ir-1];
      ra[ir-1]=ra[0];
      if (--ir == 1) {
        ra[0]=rra;
        return;
      }
    }
    i=l;
    j=l << 1;
    while (j <= ir) {
      if (j < ir && ra[j-1] < ra[j])
        ++j;
      if (rra < ra[j-1]) {
        ra[i-1]=ra[j-1];
        j += (i=j);
      } else
        j=ir+1;
    }
    ra[i-1]=rra;
  }

}
