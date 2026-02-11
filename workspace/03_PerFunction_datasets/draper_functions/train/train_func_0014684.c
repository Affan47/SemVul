modify_params(int narg, char **arg)
{
  if (narg == 0) error->all(FLERR,"Illegal min_modify command");

  int iarg = 0;
  while (iarg < narg) {
    if (strcmp(arg[iarg],"dmax") == 0) {
      if (iarg+2 > narg) error->all(FLERR,"Illegal min_modify command");
      dmax = force->numeric(FLERR,arg[iarg+1]);
      iarg += 2;
    } else if (strcmp(arg[iarg],"line") == 0) {
      if (iarg+2 > narg) error->all(FLERR,"Illegal min_modify command");
      if (strcmp(arg[iarg+1],"backtrack") == 0) linestyle = 0;
      else if (strcmp(arg[iarg+1],"quadratic") == 0) linestyle = 1;
      else if (strcmp(arg[iarg+1],"forcezero") == 0) linestyle = 2;
      else error->all(FLERR,"Illegal min_modify command");
      iarg += 2;
    } else error->all(FLERR,"Illegal min_modify command");
  }
}
