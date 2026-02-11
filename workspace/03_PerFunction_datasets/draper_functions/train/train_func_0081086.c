remove_small (FttCell * cell, gpointer * data)
{
  if (FTT_CELL_IS_LEAF (cell)) {
    GArray * sizes = data[0];
    GfsVariable * v = data[5];
    guint * min = data[1], i = GFS_VALUE (cell, v) - 1.;

    g_assert (GFS_VALUE (cell, v) > 0.);
    if (g_array_index (sizes, guint, i) < *min) {
      if (FTT_CELL_IS_ROOT (cell))
	g_log (G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "root cell belongs to a pond");
      else
	ftt_cell_destroy (cell, data[2], data[3]);
      return TRUE;
    }
    return FALSE;
  }
  else {
    FttCellChildren child;
    guint i;
    gboolean changed = FALSE;

    ftt_cell_children (cell, &child);
    for (i = 0; i < FTT_CELLS; i++)
      if (child.c[i] && remove_small (child.c[i], data))
	changed = TRUE;
    if (FTT_CELL_IS_LEAF (cell)) {

      if (FTT_CELL_IS_ROOT (cell))
	g_log (G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "root cell belongs to a pond");
      else
	ftt_cell_destroy (cell, data[2], data[3]);
    }
    else if (changed)
      gfs_cell_init_solid_fractions_from_children (cell);
    return changed;
  }
}
