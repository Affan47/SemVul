static_molecule (FILE *fp, gamgi_molecule *molecule,
gamgi_bool lights, gamgi_bool *error)
{
gamgi_dlist *dlist;
double center[3];

gamgi_math_vector_zero (center);
static_scale (fp, molecule->object.scale, center, error);


for (dlist = molecule->group_start; dlist != NULL; dlist = dlist->next)
  static_group (fp, GAMGI_CAST_GROUP dlist->data, lights, error);

for (dlist = molecule->plane_start; dlist != NULL; dlist = dlist->next)
  static_plane (fp, GAMGI_CAST_PLANE dlist->data, lights, error);

for (dlist = molecule->direction_start; dlist != NULL; dlist = dlist->next)
  static_direction (fp, GAMGI_CAST_DIRECTION dlist->data, lights, error);

for (dlist = molecule->atom_start; dlist != NULL; dlist = dlist->next)
  static_atom (fp, GAMGI_CAST_ATOM dlist->data, lights, error);

for (dlist = molecule->orbital_start; dlist != NULL; dlist = dlist->next)
  static_orbital (fp, GAMGI_CAST_ORBITAL dlist->data, lights, error);

for (dlist = molecule->text_start; dlist != NULL; dlist = dlist->next)
  static_text (fp, GAMGI_CAST_TEXT dlist->data, lights, error);

static_unscale (fp, molecule->object.scale, error);
}
