dMaxDifference (const dReal *A, const dReal *B, int n, int m)
{
  int i,j;
  int skip = dPAD(m);
  dReal diff,max;
  max = 0;
  for (i=0; i<n; i++) {
    for (j=0; j<m; j++) {
      diff = dFabs(A[i*skip+j] - B[i*skip+j]);
      if (diff > max) max = diff;
    }
  }
  return max;
}
