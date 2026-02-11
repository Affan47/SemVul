static_mark (gamgi_atom *atom, gamgi_slist *slist_neighbour)
{
gamgi_slist *slist_branch;
gamgi_bond *bond;
gamgi_atom *atom_new;
gamgi_dlist *dlist_bond;


if (atom->mark == 1) return FALSE;

if (atom->mark == -1)
  {
  slist_branch = GAMGI_CAST_SLIST slist_neighbour->data;
  while (slist_branch != NULL)
    {
    atom = GAMGI_CAST_ATOM slist_branch->data;
    atom->mark = -1;
    slist_branch = slist_branch->next;
    }

  return TRUE;
  }


atom->mark = 1;
slist_branch = GAMGI_CAST_SLIST slist_neighbour->data;
slist_branch = gamgi_engine_slist_add_start (slist_branch);
slist_neighbour->data = slist_branch;
slist_branch->data = atom;

dlist_bond = atom->bond_start;
while (dlist_bond != NULL)
  {
  bond = GAMGI_CAST_BOND dlist_bond->data;
  atom_new = bond->atom1; if (atom_new == atom) atom_new = bond->atom2;

  if (static_mark (atom_new, slist_neighbour) == TRUE) return TRUE;
  dlist_bond = dlist_bond->next;
  }

return FALSE;
}
