delete_members ()
{
  struct mapelt *map = make_map (0);
  struct mapelt mapstart;
  char **p;

  mapstart.info.name = 0;
  mapstart.next = map;
  map = &mapstart;

  lock_for_update ();

  if (files)
    for (p = files; *p; p++)
      {


	if (!strcmp (*p, "__.SYMDEF"))
	  symdef_exists = 0;
	delete_from_map (*p, map);
      }

  write_archive (map->next, 0);
}
