static_level1 (gamgi_atom *atom1, gamgi_geometry *geometry)
{
gamgi_bond *bond;
gamgi_dlist *dlist;

atom1->mark = -atom1->mark;

for (dlist = atom1->bond_start; dlist != NULL; dlist = dlist->next)
  {
  bond = GAMGI_CAST_BOND dlist->data;
  if (bond->atom1->mark > 0)
    static_level2 (atom1, bond->atom1, geometry);
  if (bond->atom2->mark > 0)
    static_level2 (atom1, bond->atom2, geometry);
  }

atom1->mark = -atom1->mark;
}
