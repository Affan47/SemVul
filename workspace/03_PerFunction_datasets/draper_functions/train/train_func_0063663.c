cell_traverse_pre_order_all (FttCell * cell,
					 gint max_depth,
					 FttCellTraverseFunc func,
					 gpointer data)
{
  FttCell * parent;

  if (max_depth >= 0 && ftt_cell_level (cell) > max_depth)
    return;

  parent = ftt_cell_parent (cell);
  (* func) (cell, data);

  g_assert (parent == NULL || parent->children != NULL);

  if (!FTT_CELL_IS_LEAF (cell)) {
    FttOct * children = cell->children;
    guint n;

    for (n = 0; n < FTT_CELLS; n++) {
      FttCell * c = &(children->cell[n]);

      if (!FTT_CELL_IS_DESTROYED (c))
	cell_traverse_pre_order_all (c, max_depth, func, data);
    }
  }
}
