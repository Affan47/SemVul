gamgi_engine_unlink_bond (gamgi_bond *bond)
{
gamgi_dlist *dlist1, *dlist2;
gamgi_atom *atom1, *atom2;

atom1 = bond->atom1;
atom2 = bond->atom2;
dlist1 = bond->dlist1;
dlist2 = bond->dlist2;


if (dlist1->next == NULL)
  atom1->bond_end = dlist1->before;

if (dlist2->next == NULL)
  atom2->bond_end = dlist2->before;


if (dlist1->before == NULL)
  atom1->bond_start = dlist1->next;

if (dlist2->before == NULL)
  atom2->bond_start = dlist2->next;


gamgi_engine_dlist_remove_start (dlist1);
gamgi_engine_dlist_remove_start (dlist2);
bond->atom1 = NULL;
bond->atom2 = NULL;
bond->dlist1 = NULL;
bond->dlist2 = NULL;
}
