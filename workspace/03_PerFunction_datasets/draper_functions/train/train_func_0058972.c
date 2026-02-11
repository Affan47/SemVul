init()
{
  if (atom->tag_enable == 0)
    error->all(FLERR,
               "Pair style granular with history requires atoms have IDs");

  int dim;
  computeflag = (int *) pair->extract("computeflag",dim);

  allocate_pages();
}
