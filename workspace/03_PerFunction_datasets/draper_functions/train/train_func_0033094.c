lubksb(double **a, int n, int *indx, double *b) const {
  int i,ii=0,ip,j;
  double sum;

  for (i = 1; i <= n; ++i){
    ip=indx[i-1];
    sum=b[ip-1];
    b[ip-1]=b[i-1];
    if (ii)
      for (j=ii;j<=i-1;j++) sum -= a[i-1][j-1]*b[j-1];
    else if (sum) ii=i;
    b[i-1]=sum;
  }
  for (i=n;i>=1;i--) {
    sum=b[i-1];
    for (j=i+1;j<=n;j++) sum -= a[i-1][j-1]*b[j-1];
    b[i-1]=sum/a[i-1][i-1];
  }
}
