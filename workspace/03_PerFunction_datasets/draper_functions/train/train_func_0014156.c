coeff(int narg, char **arg)
{
  if (narg != 4) error->all(FLERR,"Incorrect args for angle coefficients");
  if (!allocated) allocate();

  int ilo,ihi;
  force->bounds(arg[0],atom->nangletypes,ilo,ihi);

  double c_one = force->numeric(FLERR,arg[1]);
  int b_one = force->inumeric(FLERR,arg[2]);
  int n_one = force->inumeric(FLERR,arg[3]);
  if (n_one <= 0) error->all(FLERR,"Incorrect args for angle coefficients");

  int count = 0;
  for (int i = ilo; i <= ihi; i++) {
    k[i] = c_one/(n_one*n_one);
    b[i] = b_one;
    multiplicity[i] = n_one;
    setflag[i] = 1;
    count++;
  }

  if (count == 0) error->all(FLERR,"Incorrect args for angle coefficients");
}
