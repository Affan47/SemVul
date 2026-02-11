static_plane_remove (gamgi_plane *plane, gamgi_bool *link)
{
gamgi_dlist *dlist;


link[0] = link[1] = link[2] = FALSE;


if (plane->reference == GAMGI_ENGINE_ATOM)
  {
  link[0] = static_atom_parent (plane, cache.atom1);
  link[1] = static_atom_parent (plane, cache.atom2);
  link[2] = static_atom_parent (plane, cache.atom3);
  }


dlist = plane->direction_start;
while (dlist != NULL)
  { gamgi_engine_remove_direction (GAMGI_CAST_DIRECTION dlist->data);
    dlist = gamgi_engine_dlist_remove_start (dlist); }
plane->direction_start = NULL;
plane->direction_end = NULL;

dlist = plane->atom_start;
while (dlist != NULL)
  { gamgi_engine_remove_atom (GAMGI_CAST_ATOM dlist->data);
    dlist = gamgi_engine_dlist_remove_start (dlist); }
plane->atom_start = NULL;
plane->atom_end = NULL;

dlist = plane->orbital_start;
while (dlist != NULL)
  { gamgi_engine_remove_orbital (GAMGI_CAST_ORBITAL dlist->data);
    dlist = gamgi_engine_dlist_remove_start (dlist); }
plane->orbital_start = NULL;
plane->orbital_end = NULL;

dlist = plane->text_start;
while (dlist != NULL)
  { gamgi_engine_remove_text (GAMGI_CAST_TEXT dlist->data);
    dlist = gamgi_engine_dlist_remove_start (dlist); }
plane->text_start = NULL;
plane->text_end = NULL;
}
