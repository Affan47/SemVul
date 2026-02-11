delete_compute(const char *id)
{
  int icompute = find_compute(id);
  if (icompute < 0) error->all(FLERR,"Could not find compute ID to delete");
  delete compute[icompute];


  for (int i = icompute+1; i < ncompute; i++) compute[i-1] = compute[i];
  ncompute--;
}
