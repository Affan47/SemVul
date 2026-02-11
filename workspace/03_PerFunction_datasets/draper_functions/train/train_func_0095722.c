init_one(int i, int j)
{
  if (setflag[i][j] == 0) error->all(FLERR,"All pair coeffs are not set");


  cut3rebo = 3.0 * r_2;


  double cutmax = MAX( cut3rebo,r_2_LR );

  cutghost[i][j] = r_2;
  cutLRsq = r_2_LR*r_2_LR;

  cutghost[j][i] = cutghost[i][j];

  r_2_sq = r_2*r_2;

  return cutmax;
}
