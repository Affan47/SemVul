reset_pathsearch (void)
{
  int i;

  for (i = 0; i < hfieldsize * vfieldsize; i++)
    field[i].pathsearch = -1;
}
