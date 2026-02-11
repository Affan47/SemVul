cell_traverse_boundary_level_leafs (FttCell * cell,
						FttDirection d,
						gint max_depth,
						FttCellTraverseFunc func,
						gpointer data)
{
  if (ftt_cell_level (cell) == max_depth || FTT_CELL_IS_LEAF (cell))
    (* func) (cell, data);
  else if (!FTT_CELL_IS_LEAF (cell)) {
    FttCellChildren children;
    guint i, n;

    n = ftt_cell_children_direction (cell, d, &children);
    for (i = 0; i < n; i++)
      if (children.c[i])
	cell_traverse_boundary_level_leafs (children.c[i], d,
					    max_depth, func, data);
  }
}
