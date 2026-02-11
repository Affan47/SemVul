gamgi_mesa_center_cluster (gamgi_cluster *cluster, double *sum, unsigned int *number)
{
gamgi_dlist *dlist;

gamgi_math_vector_add (sum, cluster->center, sum);
*number += 1;

dlist = cluster->cluster_start;
while (dlist != NULL)
  { gamgi_mesa_center_cluster (GAMGI_CAST_CLUSTER dlist->data, sum, number);
    dlist = dlist->next; }

dlist = cluster->molecule_start;
while (dlist != NULL)
  { gamgi_mesa_center_molecule (GAMGI_CAST_MOLECULE dlist->data, sum, number);
    dlist = dlist->next; }

dlist = cluster->group_start;
while (dlist != NULL)
  { gamgi_mesa_center_group (GAMGI_CAST_GROUP dlist->data, sum, number);
    dlist = dlist->next; }

dlist = cluster->plane_start;
while (dlist != NULL)
  { gamgi_mesa_center_plane (GAMGI_CAST_PLANE dlist->data, sum, number);
    dlist = dlist->next; }

dlist = cluster->direction_start;
while (dlist != NULL)
  { gamgi_mesa_center_direction (GAMGI_CAST_DIRECTION dlist->data, sum, number);
    dlist = dlist->next; }

dlist = cluster->atom_start;
while (dlist != NULL)
  { gamgi_mesa_center_atom (GAMGI_CAST_ATOM dlist->data, sum, number);
    dlist = dlist->next; }
}
