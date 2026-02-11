lib3ds_matrix_scale(Lib3dsMatrix m, Lib3dsVector s)
{
  int i;

  for (i=0; i<4; i++) {
    m[0][i]*=s[0];
    m[1][i]*=s[1];
    m[2][i]*=s[2];
  }
}
