settings(int narg, char **arg)
{
  if (narg != 6) error->all(FLERR,"Illegal pair_style command");

  kn = force->numeric(FLERR,arg[0]);
  if (strcmp(arg[1],"NULL") == 0) kt = kn * 2.0/7.0;
  else kt = force->numeric(FLERR,arg[1]);

  gamman = force->numeric(FLERR,arg[2]);
  if (strcmp(arg[3],"NULL") == 0) gammat = 0.5 * gamman;
  else gammat = force->numeric(FLERR,arg[3]);

  xmu = force->numeric(FLERR,arg[4]);
  dampflag = force->inumeric(FLERR,arg[5]);
  if (dampflag == 0) gammat = 0.0;

  if (kn < 0.0 || kt < 0.0 || gamman < 0.0 || gammat < 0.0 ||
      xmu < 0.0 || xmu > 10000.0 || dampflag < 0 || dampflag > 1)
    error->all(FLERR,"Illegal pair_style command");


  kn /= force->nktv2p;
  kt /= force->nktv2p;
}
