read_cube_file(struct cube_reader *rd, GError **error,
			  gboolean withDensity)
{

  DBG_fprintf(stderr, "Cube: reading file as a cube file.\n");


  rd->line      = g_string_new("");
  rd->comment   = (gchar*)0;


  rd->ntype     = 0;
  rd->elements  = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, g_free);
  rd->nodeTypes = (VisuElement**)0;

  rd->coords    = (float*)0;
  rd->density   = (GArray*)0;


  if (!read_comment(rd, error))
    {
      DBG_fprintf(stderr, "Cube: no comment, not a cube file.\n");
      return -1;
    }
  if (!read_natom(rd, error))
    return -1;
  if (!read_box(rd, error))
    return -1;

  if (!read_coords(rd, error))
    return 1;
  if (withDensity)
    {
      if (!read_density(rd, error))
	return 1;
    }
  return 0;
}
