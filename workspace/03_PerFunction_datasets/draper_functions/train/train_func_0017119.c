ftt_refine_corner (const FttCell * cell)
{
  FttCellNeighbors neighbor;
  guint i;

  g_return_val_if_fail (cell != NULL, FALSE);

  ftt_cell_neighbors (cell, &neighbor);
  for (i = 0; i < FTT_NEIGHBORS; i++) {
    FttCell * n = neighbor.c[i];

    if (n && !FTT_CELL_IS_LEAF (n)) {
      FttCellChildren child;
      guint j, k;

      k = ftt_cell_children_direction (n, FTT_OPPOSITE_DIRECTION (i), &child);
      for (j = 0; j < k; j++) {
	FttCell * c = child.c[j];

	if (c) {
#if FTT_2D
	  static guint perpendicular[FTT_NEIGHBORS_2D][FTT_CELLS/2] =
	  {{2,3},
	   {2,3},
	   {1,0},
	   {1,0}};
	  FttCell * nc = ftt_cell_neighbor (c, perpendicular[i][j]);

	  if (nc && !FTT_CELL_IS_LEAF (nc))
	    return TRUE;
#else
	  static guint perpendicular[FTT_NEIGHBORS][FTT_CELLS/2][2] =
	  {{{4,2},{4,3},{5,2},{5,3}},
	   {{4,2},{4,3},{5,2},{5,3}},
	   {{4,1},{4,0},{5,1},{5,0}},
	   {{4,1},{4,0},{5,1},{5,0}},
	   {{2,1},{2,0},{3,1},{3,0}},
	   {{2,1},{2,0},{3,1},{3,0}}};
	  FttCell * nc0, * nc1;

	  nc0 = ftt_cell_neighbor (c, perpendicular[i][j][0]);
	  if (nc0 && !FTT_CELL_IS_LEAF (nc0))
	    return TRUE;
	  nc1 = ftt_cell_neighbor (c, perpendicular[i][j][1]);
	  if (nc1 && !FTT_CELL_IS_LEAF (nc1))
	    return TRUE;
#endif
	  if (!FTT_CELL_IS_LEAF (c)) {
	    FttCellChildren child;
	    guint j, k;

	    k = ftt_cell_children_direction (c, FTT_OPPOSITE_DIRECTION (i), &child);
	    for (j = 0; j < k; j++)
	      if (child.c[j])
		return TRUE;
	  }
	}
      }
    }
  }

  return FALSE;
}
