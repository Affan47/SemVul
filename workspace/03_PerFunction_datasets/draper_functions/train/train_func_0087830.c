gamgi_engine_copy_group (gamgi_group *group)
{
gamgi_dlist *dlist;
gamgi_text *text_new;
gamgi_orbital *orbital_new;
gamgi_atom *atom_new;
gamgi_direction *direction_new;
gamgi_plane *plane_new;
gamgi_group *group_new, *group_child;

group_new = gamgi_engine_create_group ();
static_start (GAMGI_CAST_OBJECT group_new);
gamgi_engine_copy_out_group (group, group_new);
group_new->object.number = gamgi_engine_number_group_get ();

dlist = group->group_start;
while (dlist != NULL)
  { group_child = gamgi_engine_copy_group (GAMGI_CAST_GROUP dlist->data);
    gamgi_engine_link_group_group (group_child, group_new);
    dlist = dlist->next; }

dlist = group->plane_start;
while (dlist != NULL)
  { plane_new = gamgi_engine_copy_plane (GAMGI_CAST_PLANE dlist->data);
    gamgi_engine_link_plane_group (plane_new, group_new);
    dlist = dlist->next; }

dlist = group->direction_start;
while (dlist != NULL)
  { direction_new = gamgi_engine_copy_direction (GAMGI_CAST_DIRECTION dlist->data);
    gamgi_engine_link_direction_group (direction_new, group_new);
    dlist = dlist->next; }

dlist = group->atom_start;
while (dlist != NULL)
  { atom_new = gamgi_engine_copy_atom (GAMGI_CAST_ATOM dlist->data);
    gamgi_engine_link_atom_group (atom_new, group_new);
    dlist = dlist->next; }

dlist = group->orbital_start;
while (dlist != NULL)
  { orbital_new = gamgi_engine_copy_orbital (GAMGI_CAST_ORBITAL dlist->data);
    gamgi_engine_link_orbital_group (orbital_new, group_new);
    dlist = dlist->next; }

dlist = group->text_start;
while (dlist != NULL)
  { text_new = gamgi_engine_copy_text (GAMGI_CAST_TEXT dlist->data);
    gamgi_engine_link_text_group (text_new, group_new);
    dlist = dlist->next; }

return group_new;
}
