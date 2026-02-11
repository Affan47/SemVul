options(int narg, char **arg)
{
  if (narg < 0) error->all(FLERR,"Illegal change_box command");

  scaleflag = 1;

  int iarg = 0;
  while (iarg < narg) {
    if (strcmp(arg[iarg],"units") == 0) {
      if (iarg+2 > narg) error->all(FLERR,"Illegal change_box command");
      if (strcmp(arg[iarg+1],"box") == 0) scaleflag = 0;
      else if (strcmp(arg[iarg+1],"lattice") == 0) scaleflag = 1;
      else error->all(FLERR,"Illegal change_box command");
      iarg += 2;
    } else error->all(FLERR,"Illegal change_box command");
  }
}
