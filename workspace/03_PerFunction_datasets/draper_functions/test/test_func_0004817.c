delete_region(int narg, char **arg)
{
  if (narg < 2) error->all(FLERR,"Illegal delete_atoms command");

  int iregion = domain->find_region(arg[1]);
  if (iregion == -1) error->all(FLERR,"Could not find delete_atoms region ID");
  options(narg-2,&arg[2]);


  int nlocal = atom->nlocal;
  memory->create(dlist,nlocal,"delete_atoms:dlist");
  for (int i = 0; i < nlocal; i++) dlist[i] = 0;

  double **x = atom->x;

  for (int i = 0; i < nlocal; i++)
    if (domain->regions[iregion]->match(x[i][0],x[i][1],x[i][2])) dlist[i] = 1;

  if (mol_flag == 0) return;


  hash = new std::map<int,int>();

  int *molecule = atom->molecule;
  for (int i = 0; i < nlocal; i++)
    if (dlist[i] && hash->find(molecule[i]) == hash->end())
      (*hash)[molecule[i]] = 1;

  int n = hash->size();
  int *list;
  memory->create(list,n,"delete_atoms:list");

  n = 0;
  std::map<int,int>::iterator pos;
  for (pos = hash->begin(); pos != hash->end(); ++pos) list[n++] = pos->first;

  cptr = this;
  comm->ring(n,sizeof(int),list,1,molring,NULL);

  delete hash;
  memory->destroy(list);
}
