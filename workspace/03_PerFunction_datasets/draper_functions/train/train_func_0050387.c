_dl_check_all_versions (struct link_map *map, int verbose, int trace_mode)
{
  struct link_map *l;
  int result = 0;

  for (l = map; l != NULL; l = l->l_next)
    result |= (! l->l_faked
	       && _dl_check_map_versions (l, verbose, trace_mode));

  return result;
}
