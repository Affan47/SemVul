gamgi_mesa_translate_layer (gamgi_layer *layer, double *translate)
{
gamgi_dlist *dlist;

gamgi_mesa_translate_out_layer (layer, translate);

dlist = layer->assembly_start;
while (dlist != NULL)
  { gamgi_mesa_translate_assembly (GAMGI_CAST_ASSEMBLY dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->graph_start;
while (dlist != NULL)
  { gamgi_mesa_translate_graph (GAMGI_CAST_GRAPH dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->shape_start;
while (dlist != NULL)
  { gamgi_mesa_translate_shape (GAMGI_CAST_SHAPE dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->arrow_start;
while (dlist != NULL)
  {  gamgi_mesa_translate_arrow (GAMGI_CAST_ARROW dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->cell_start;
while (dlist != NULL)
  { gamgi_mesa_translate_cell (GAMGI_CAST_CELL dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->cluster_start;
while (dlist != NULL)
  { gamgi_mesa_translate_cluster (GAMGI_CAST_CLUSTER dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->molecule_start;
while (dlist != NULL)
  { gamgi_mesa_translate_molecule (GAMGI_CAST_MOLECULE dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->group_start;
while (dlist != NULL)
  { gamgi_mesa_translate_group (GAMGI_CAST_GROUP dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->plane_start;
while (dlist != NULL)
  { gamgi_mesa_translate_plane (GAMGI_CAST_PLANE dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->direction_start;
while (dlist != NULL)
  { gamgi_mesa_translate_direction (GAMGI_CAST_DIRECTION dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->atom_start;
while (dlist != NULL)
  { gamgi_mesa_translate_atom (GAMGI_CAST_ATOM dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->orbital_start;
while (dlist != NULL)
  { gamgi_mesa_translate_orbital (GAMGI_CAST_ORBITAL dlist->data, translate);
    dlist = dlist->next; }

dlist = layer->text_start;
while (dlist != NULL)
  { gamgi_mesa_translate_text (GAMGI_CAST_TEXT dlist->data, translate);
    dlist = dlist->next; }
}
