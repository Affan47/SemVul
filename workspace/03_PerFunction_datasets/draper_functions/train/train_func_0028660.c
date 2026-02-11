coeff(int narg, char **arg)
{
  if (narg != 7) error->all(FLERR,"Incorrect args for pair coefficients");
  if (!allocated) allocate();

  int ilo,ihi,jlo,jhi;
  force->bounds(arg[0],atom->ntypes,ilo,ihi);
  force->bounds(arg[1],atom->ntypes,jlo,jhi);

  double bulkmodulus_one = force->numeric(FLERR,arg[2]);
  double shearmodulus_one = force->numeric(FLERR,arg[3]);
  double cut_one = force->numeric(FLERR,arg[4]);
  double s00_one = force->numeric(FLERR,arg[5]);
  double alpha_one = force->numeric(FLERR,arg[6]);

  int count = 0;
  for (int i = ilo; i <= ihi; i++) {
    for (int j = MAX(jlo,i); j <= jhi; j++) {
      bulkmodulus[i][j] = bulkmodulus_one;
      shearmodulus[i][j] = shearmodulus_one;
      cut[i][j] = cut_one;
      s00[i][j] = s00_one;
      alpha[i][j] = alpha_one;
      setflag[i][j] = 1;
      count++;
    }
  }

  if (count == 0) error->all(FLERR,"Incorrect args for pair coefficients");
}
