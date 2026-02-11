add_line_map (set, reason, sysp, from_line, to_file, to_line)
     struct line_maps *set;
     enum lc_reason reason;
     unsigned int sysp;
     unsigned int from_line;
     const char *to_file;
     unsigned int to_line;
{
  struct line_map *map;

  if (set->used && from_line < set->maps[set->used - 1].from_line)
    abort ();

  if (set->used == set->allocated)
    {
      set->allocated = 2 * set->allocated + 256;
      set->maps = (struct line_map *)
	xrealloc (set->maps, set->allocated * sizeof (struct line_map));
    }

  map = &set->maps[set->used++];


  if (set->depth == 0)
    reason = LC_ENTER;
  else if (reason == LC_LEAVE)
    {
      struct line_map *from;
      bool error;

      if (MAIN_FILE_P (map - 1))
	{
	  error = true;
	  reason = LC_RENAME;
	  from = map - 1;
	}
      else
	{
	  from = INCLUDED_FROM (set, map - 1);
	  error = to_file && strcmp (from->to_file, to_file);
	}


      if (error)
	fprintf (stderr, "line-map.c: file \"%s\" left but not entered\n",
		 to_file);


      if (error || to_file == NULL)
	{
	  to_file = from->to_file;
	  to_line = LAST_SOURCE_LINE (from) + 1;
	  sysp = from->sysp;
	}
    }

  map->reason = reason;
  map->sysp = sysp;
  map->from_line = from_line;
  map->to_file = to_file;
  map->to_line = to_line;

  if (reason == LC_ENTER)
    {
      set->depth++;
      map->included_from = set->used - 2;
      if (set->trace_includes)
	trace_include (set, map);
    }
  else if (reason == LC_RENAME)
    map->included_from = map[-1].included_from;
  else if (reason == LC_LEAVE)
    {
      set->depth--;
      map->included_from = INCLUDED_FROM (set, map - 1)->included_from;
    }

  return map;
}
