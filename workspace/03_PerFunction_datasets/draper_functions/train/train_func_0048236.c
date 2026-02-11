newmat2mat44(const Matrix& nmat)
{
  mat44 ret;
  for (int i=1; i<=4; i++) {
    for (int j=1; j<=4; j++) {
      ret.m[i-1][j-1] = nmat(i,j);
    }
  }
  return ret;
}
