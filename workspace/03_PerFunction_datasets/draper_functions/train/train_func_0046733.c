modify_fix(int narg, char **arg)
{
  if (narg < 2) error->all(FLERR,"Illegal fix_modify command");


  int ifix;
  for (ifix = 0; ifix < nfix; ifix++)
    if (strcmp(arg[0],fix[ifix]->id) == 0) break;
  if (ifix == nfix) error->all(FLERR,"Could not find fix_modify ID");

  fix[ifix]->modify_params(narg-1,&arg[1]);
}
