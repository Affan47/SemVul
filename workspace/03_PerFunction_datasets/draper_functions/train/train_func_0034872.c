coeff(int narg, char **arg)
{
  if (narg < 2) error->all(FLERR,"Incorrect args for improper coefficients");
  if (!allocated) allocate();

  int ilo,ihi;
  force->bounds(arg[0],atom->nimpropertypes,ilo,ihi);

  int count = 0;

  if (strcmp(arg[1],"aa") == 0) {
    if (narg != 8) error->all(FLERR,"Incorrect args for improper coefficients");

    double k1_one = force->numeric(FLERR,arg[2]);
    double k2_one = force->numeric(FLERR,arg[3]);
    double k3_one = force->numeric(FLERR,arg[4]);
    double theta0_1_one = force->numeric(FLERR,arg[5]);
    double theta0_2_one = force->numeric(FLERR,arg[6]);
    double theta0_3_one = force->numeric(FLERR,arg[7]);


    for (int i = ilo; i <= ihi; i++) {
      aa_k1[i] = k1_one;
      aa_k2[i] = k2_one;
      aa_k3[i] = k3_one;
      aa_theta0_1[i] = theta0_1_one/180.0 * MY_PI;
      aa_theta0_2[i] = theta0_2_one/180.0 * MY_PI;
      aa_theta0_3[i] = theta0_3_one/180.0 * MY_PI;
      setflag_aa[i] = 1;
      count++;
    }

  } else {
    if (narg != 3) error->all(FLERR,"Incorrect args for improper coefficients");

    double k0_one = force->numeric(FLERR,arg[1]);
    double chi0_one = force->numeric(FLERR,arg[2]);


    for (int i = ilo; i <= ihi; i++) {
      k0[i] = k0_one;
      chi0[i] = chi0_one/180.0 * MY_PI;
      setflag_i[i] = 1;
      count++;
    }
  }

  if (count == 0) error->all(FLERR,"Incorrect args for improper coefficients");

  for (int i = ilo; i <= ihi; i++)
    if (setflag_i[i] == 1 && setflag_aa[i] == 1) setflag[i] = 1;
}
