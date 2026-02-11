mat44_to_mat33(mat44 x)
{
  mat33 y;
  int i,j;
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      y.m[i][j] = x.m[i][j];
    }
  }
  return y;
}
