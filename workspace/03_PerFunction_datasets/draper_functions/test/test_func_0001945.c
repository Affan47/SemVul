gamgi_chem_bond_half_remove (gamgi_object *scope)
{
gamgi_atom *atom;
gamgi_bond *bond;
gamgi_dlist *atom_start, *dlist_a, *dlist_b;


atom_start = gamgi_engine_dlist_atom_object (scope, NULL);


for (dlist_a = atom_start; dlist_a != NULL; dlist_a = dlist_a->next)
  {
  atom = GAMGI_CAST_ATOM dlist_a->data;

  dlist_b = atom->bond_start;
  while (dlist_b != NULL)
    {
    bond = GAMGI_CAST_BOND dlist_b->data;
    dlist_b = dlist_b->next;

    if (bond->first == TRUE)
      bond->first = FALSE;
    else
      bond->first = TRUE;
    }
  }


for (dlist_a = atom_start; dlist_a != NULL; dlist_a = dlist_a->next)
  {
  atom = GAMGI_CAST_ATOM dlist_a->data;

  dlist_b = atom->bond_start;
  while (dlist_b != NULL)
    {
    bond = GAMGI_CAST_BOND dlist_b->data;
    dlist_b = dlist_b->next;

    if (bond->first == FALSE)
      {
      gamgi_engine_unlink_bond (bond);
      gamgi_engine_remove_bond (bond);
      }

    }
  }


gamgi_engine_dlist_remove_all (atom_start);
}
