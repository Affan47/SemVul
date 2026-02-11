coeff(int narg, char **arg)
{
  if (narg != 3)
    error->all(FLERR,"Incorrect args for pair coefficients");
  if (!allocated) allocate();

  int ilo,ihi;
  force->bounds(arg[0],atom->ntypes,ilo,ihi);

  int jlo,jhi;
  force->bounds(arg[1],atom->ntypes,jlo,jhi);

  double z_one = force->numeric(FLERR,arg[2]);


  int count = 0;
  for (int i = ilo; i <= ihi; i++) {
    for (int j = MAX(jlo,i); j <= jhi; j++) {
      if (i == j) z[i] = z_one;
      setflag[i][j] = 1;
      count++;
    }
  }

  if (count == 0) error->all(FLERR,"Incorrect args for pair coefficients");
}
