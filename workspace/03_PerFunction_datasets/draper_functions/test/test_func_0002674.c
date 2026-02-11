gamgi_engine_find_orbital_assembly (unsigned int number,
gamgi_assembly *assembly)
{
gamgi_orbital *orbital;
gamgi_dlist *dlist;

dlist = assembly->orbital_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_orbital (number,
  GAMGI_CAST_ORBITAL dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->atom_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_atom (number,
  GAMGI_CAST_ATOM dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->direction_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_direction (number,
  GAMGI_CAST_DIRECTION dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->plane_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_plane (number,
  GAMGI_CAST_PLANE dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->group_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_group (number,
  GAMGI_CAST_GROUP dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->molecule_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_molecule (number,
  GAMGI_CAST_MOLECULE dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->cluster_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_cluster (number,
  GAMGI_CAST_CLUSTER dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->cell_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_cell (number,
  GAMGI_CAST_CELL dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

dlist = assembly->assembly_start;
while (dlist != NULL)
  {
  orbital = gamgi_engine_find_orbital_assembly (number,
  GAMGI_CAST_ASSEMBLY dlist->data);
  if (orbital != NULL) return orbital;
  dlist = dlist->next;
  }

return NULL;
}
