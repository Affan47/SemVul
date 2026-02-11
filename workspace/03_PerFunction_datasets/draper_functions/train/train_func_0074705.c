clear_lim_data (gimple stmt)
{
  void **p = pointer_map_contains (lim_aux_data_map, stmt);
  if (!p)
    return;

  free_lim_aux_data ((struct lim_aux_data *) *p);
  *p = NULL;
}
