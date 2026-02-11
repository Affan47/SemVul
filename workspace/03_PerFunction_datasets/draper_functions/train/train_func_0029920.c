max_level_fct(const EL_INFO *el_info, void *data)
{
  ((COARSEN_TRAVERSE_DATA *)data)->max_level_val =
    MAX(((COARSEN_TRAVERSE_DATA *)data)->max_level_val, el_info->level);
}
