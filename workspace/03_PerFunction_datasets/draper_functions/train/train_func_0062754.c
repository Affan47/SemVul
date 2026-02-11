cmd_delkmap (int interactive UNUSED, struct cmdarg **args)
{
   rp_keymap *map, *top, *root;

  top = find_keymap (defaults.top_kmap);
  root = find_keymap (ROOT_KEYMAP);

  map = ARG(0,keymap);
  if (map == root || map == top)
    return cmdret_new (RET_FAILURE, "delkmap: cannot delete keymap '%s'", ARG_STRING(0));

  list_del (&map->node);

  return cmdret_new (RET_SUCCESS, NULL);
}
