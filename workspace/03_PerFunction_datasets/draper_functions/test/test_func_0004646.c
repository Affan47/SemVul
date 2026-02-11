init_one(int i, int j)
{
  if (setflag[i][j] == 0) error->all(FLERR,"All pair coeffs are not set");

  bulkmodulus[j][i] = bulkmodulus[i][j];
  shearmodulus[j][i] = shearmodulus[i][j];
  s00[j][i] = s00[i][j];
  alpha[j][i] = alpha[i][j];
  cut[j][i] = cut[i][j];
  m_lambdai[j][i] = m_lambdai[i][j];
  m_taubi[j][i] = m_taubi[i][j];

  return cut[i][j];
}
