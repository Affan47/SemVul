init()
{


  int ifix = modify->find_fix(id_fix);
  if (ifix < 0) error->all(FLERR,"Could not find compute displace/atom fix ID");
  fix = (FixStore *) modify->fix[ifix];
}
