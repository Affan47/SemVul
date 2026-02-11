coeff(int narg, char **arg)
{
  if (narg < 4) error->all(FLERR,"Incorrect args for dihedral coefficients");
  if (!allocated) allocate();

  int ilo,ihi;
  force->bounds(arg[0],atom->ndihedraltypes,ilo,ihi);


  double k_one;
  int multiplicity_one;
  double shift_one;
  int nterms_one = force->inumeric(FLERR,arg[1]);

  if (nterms_one < 1)
    error->all(FLERR,"Incorrect number of terms arg for dihedral coefficients");

  if (2+3*nterms_one < narg)
    error->all(FLERR,"Incorrect number of arguments for dihedral coefficients");

  int count = 0;
  for (int i = ilo; i <= ihi; i++) {
    nterms[i] = nterms_one;
    k[i] = new double [nterms_one];
    multiplicity[i] = new int [nterms_one];
    shift[i] = new double [nterms_one];
    cos_shift[i] = new double [nterms_one];
    sin_shift[i] = new double [nterms_one];
    for (int j = 0; j<nterms_one; j++) {
      int offset = 1+3*j;
      k_one = force->numeric(FLERR,arg[offset+1]);
      multiplicity_one = force->inumeric(FLERR,arg[offset+2]);
      shift_one = force->numeric(FLERR,arg[offset+3]);
      k[i][j] = k_one;
      multiplicity[i][j] = multiplicity_one;
      shift[i][j] = shift_one;
      cos_shift[i][j] = cos(MY_PI*shift_one/180.0);
      sin_shift[i][j] = sin(MY_PI*shift_one/180.0);
    }
    setflag[i] = 1;
    count++;
  }

  if (count == 0) error->all(FLERR,"Incorrect args for dihedral coefficients");
}
