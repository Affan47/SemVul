settings(int narg, char **arg)
{
  if (narg != 2 && narg != 3) error->all(FLERR,"Illegal pair_style command");

  cut_lj_inner = force->numeric(FLERR,arg[0]);
  cut_lj = force->numeric(FLERR,arg[1]);
  if (narg == 2) cut_coul = cut_lj;
  else cut_coul = force->numeric(FLERR,arg[2]);
}
