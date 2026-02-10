gamgi_engine_link_plane_assembly (gamgi_plane *plane,
gamgi_assembly *assembly)
{
gamgi_dlist *dlist;


dlist = gamgi_engine_dlist_add_end (assembly->plane_end);
assembly->plane_end = dlist;
if (dlist->before == NULL) assembly->plane_start = dlist;


dlist->data = plane;
plane->object.dlist = dlist;
plane->object.object = GAMGI_CAST_OBJECT assembly;
}
