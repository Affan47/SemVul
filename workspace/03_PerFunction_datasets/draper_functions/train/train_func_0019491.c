gamgi_mesa_rotate_atom (gamgi_atom *atom,
double *quaternion, double *rotate, double *center)
{
gamgi_bond *bond;
gamgi_dlist *dlist;

gamgi_mesa_rotate_out_atom (atom, quaternion, rotate, center);


dlist = atom->bond_start;
while (dlist != NULL)
  {
  bond = GAMGI_CAST_BOND dlist->data;
  dlist = dlist->next;

  if (bond->atom2 == NULL) continue;
  if (bond->first == TRUE) { bond->first = FALSE; continue; }
  else bond->first = TRUE;

  gamgi_mesa_rotate_bond (bond, quaternion, rotate, center);
  }

dlist = atom->orbital_start;
while (dlist != NULL)
  { gamgi_mesa_rotate_orbital (GAMGI_CAST_ORBITAL dlist->data, quaternion, rotate, center);
    dlist = dlist->next; }

dlist = atom->text_start;
while (dlist != NULL)
  { gamgi_mesa_rotate_text (GAMGI_CAST_TEXT dlist->data, quaternion, rotate, center);
    dlist = dlist->next; }
}
