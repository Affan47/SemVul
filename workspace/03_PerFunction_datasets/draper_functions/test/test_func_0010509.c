region_function(char *id)
{
  int iregion = domain->find_region(id);
  if (iregion == -1)
    error->all(FLERR,"Region ID in variable formula does not exist");


  domain->regions[iregion]->init();

  return iregion;
}
