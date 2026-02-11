selection(int n)
{
  delete [] select;
  select = new int[n];
  int nlo,nhi;

  if (style == ATOM_SELECT) {
    if (atom->tag_enable == 0)
      error->all(FLERR,"Cannot use set atom with no atom IDs defined");
    force->bounds(id,BIG,nlo,nhi);

    int *tag = atom->tag;
    for (int i = 0; i < n; i++)
      if (tag[i] >= nlo && tag[i] <= nhi) select[i] = 1;
      else select[i] = 0;

  } else if (style == MOL_SELECT) {
    if (atom->molecule_flag == 0)
      error->all(FLERR,"Cannot use set mol with no molecule IDs defined");
    else force->bounds(id,BIG,nlo,nhi,0);

    int *molecule = atom->molecule;
    for (int i = 0; i < n; i++)
      if (molecule[i] >= nlo && molecule[i] <= nhi) select[i] = 1;
      else select[i] = 0;

  } else if (style == TYPE_SELECT) {
    force->bounds(id,atom->ntypes,nlo,nhi);

    int *type = atom->type;
    for (int i = 0; i < n; i++)
      if (type[i] >= nlo && type[i] <= nhi) select[i] = 1;
      else select[i] = 0;

  } else if (style == GROUP_SELECT) {
    int igroup = group->find(id);
    if (igroup == -1) error->all(FLERR,"Could not find set group ID");
    int groupbit = group->bitmask[igroup];

    int *mask = atom->mask;
    for (int i = 0; i < n; i++)
      if (mask[i] & groupbit) select[i] = 1;
      else select[i] = 0;

  } else if (style == REGION_SELECT) {
    int iregion = domain->find_region(id);
    if (iregion == -1) error->all(FLERR,"Set region ID does not exist");

    double **x = atom->x;
    for (int i = 0; i < n; i++)
      if (domain->regions[iregion]->match(x[i][0],x[i][1],x[i][2]))
        select[i] = 1;
      else select[i] = 0;
  }
}
