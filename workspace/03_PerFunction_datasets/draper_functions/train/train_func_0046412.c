init_one(int i, int j)
{
  if (setflag[i][j] == 0) error->all(FLERR,"All pair coeffs are not set");

  kspring[j][i] = kspring[i][j];
  alpha[j][i] = alpha[i][j];
  s00[j][i] = s00[i][j];
  cut[j][i] = cut[i][j];

  return cut[i][j];
}
