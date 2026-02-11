coeff(int narg, char **arg)
{
  if (narg < 5 || narg > 6)
    error->all(FLERR,"Incorrect args for pair coefficients");
  if (!allocated) allocate();

  int ilo,ihi,jlo,jhi;
  force->bounds(*(arg++),atom->ntypes,ilo,ihi);
  force->bounds(*(arg++),atom->ntypes,jlo,jhi);

  double buck_a_one = force->numeric(FLERR,*(arg++));
  double buck_rho_one = force->numeric(FLERR,*(arg++));
  double buck_c_one = force->numeric(FLERR,*(arg++));

  double cut_buck_one = cut_buck_global;
  if (narg == 6) cut_buck_one = force->numeric(FLERR,*(arg++));

  int count = 0;
  for (int i = ilo; i <= ihi; i++) {
    for (int j = MAX(jlo,i); j <= jhi; j++) {
      buck_a_read[i][j] = buck_a_one;
      buck_c_read[i][j] = buck_c_one;
      buck_rho_read[i][j] = buck_rho_one;
      cut_buck_read[i][j] = cut_buck_one;
      setflag[i][j] = 1;
      count++;
    }
  }

  if (count == 0) error->all(FLERR,"Incorrect args for pair coefficients");
}
