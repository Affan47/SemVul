static_link (gamgi_plane *plane, double thickness,
gamgi_dlist *start, double *normal)
{
gamgi_atom *atom;
gamgi_dlist *dlist;
double r[3];
double length;


for (dlist = start; dlist != NULL; dlist = dlist->next)
  {
  atom = GAMGI_CAST_ATOM dlist->data;

  gamgi_math_vector_sub (atom->position, plane->center, r);
  length = gamgi_math_vector_dot (r, normal);

  if (fabs (length) < thickness)
    {
    gamgi_engine_unlink_atom (atom);
    gamgi_engine_link_atom_plane (atom, plane);
    }
  }
}
