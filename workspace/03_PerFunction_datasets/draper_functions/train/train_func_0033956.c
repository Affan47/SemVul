gfs_cell_fluid (FttCell * cell)
{
  g_return_if_fail (cell != NULL);

  if (GFS_STATE (cell)->solid) {
    g_free (GFS_STATE (cell)->solid);
    GFS_STATE (cell)->solid = NULL;
  }

  if (!FTT_CELL_IS_LEAF (cell)) {
    FttCellChildren child;
    guint i;

    ftt_cell_children (cell, &child);
    for (i = 0; i < FTT_CELLS; i++)
      if (child.c[i])
	gfs_cell_fluid (child.c[i]);
  }
}
