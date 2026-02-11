pair_check()
{
  if (force->pair == NULL)
    error->all(FLERR,"KSpace solver requires a pair style");
  if (ewaldflag && force->pair->ewaldflag == 0)
    error->all(FLERR,"KSpace style is incompatible with Pair style");
  if (pppmflag && force->pair->pppmflag == 0)
    error->all(FLERR,"KSpace style is incompatible with Pair style");
  if (msmflag && force->pair->msmflag == 0)
    error->all(FLERR,"KSpace style is incompatible with Pair style");
  if (dispersionflag && force->pair->dispersionflag == 0)
    error->all(FLERR,"KSpace style is incompatible with Pair style");
  if (tip4pflag && force->pair->tip4pflag == 0)
    error->all(FLERR,"KSpace style is incompatible with Pair style");
  if (dipoleflag && force->pair->dipoleflag == 0)
    error->all(FLERR,"KSpace style is incompatible with Pair style");
}
