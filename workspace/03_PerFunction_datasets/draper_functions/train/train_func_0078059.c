ftt_cell_coarsen (FttCell * root,
			   FttCellCoarsenFunc coarsen,
			   gpointer coarsen_data,
			   FttCellCleanupFunc cleanup,
			   gpointer cleanup_data)
{
  guint i, n;
  gboolean coarsenable = TRUE;

  g_return_val_if_fail (root != NULL, FALSE);
  g_return_val_if_fail (coarsen != NULL, FALSE);

  if (FTT_CELL_IS_LEAF (root))
    return (* coarsen) (root, coarsen_data);

  for (i = 0; i < FTT_CELLS; i++)
    if (!FTT_CELL_IS_DESTROYED (&(root->children->cell[i])))
      coarsenable &= ftt_cell_coarsen (&(root->children->cell[i]),
				       coarsen, coarsen_data,
				       cleanup, cleanup_data);
  if (!coarsenable || !(* coarsen) (root, coarsen_data))
    return FALSE;

  {
    FttDirection d;

    for (d = 0; d < FTT_NEIGHBORS; d++) {
      FttCellChildren child;

      n = ftt_cell_children_direction (root, d, &child);
      for (i = 0; i < n; i++) {
	FttCell * neighbor;

	if (child.c[i] && (neighbor = ftt_cell_neighbor (child.c[i], d)) &&
	    !FTT_CELL_IS_LEAF (neighbor)) {
	  FttCellChildren child1;
	  guint j, k;
	  gboolean empty = TRUE;

	  k = ftt_cell_children_direction (neighbor, FTT_OPPOSITE_DIRECTION (d), &child1);
	  for (j = 0; j < k && empty; j++)
	    if (child1.c[j])
	      empty = FALSE;
	  if (!empty && !ftt_cell_coarsen (neighbor, coarsen, coarsen_data,
					   cleanup, cleanup_data))
	    return FALSE;
	  if (!FTT_CELL_IS_LEAF (neighbor))
	    neighbor->children->neighbors.c[FTT_OPPOSITE_DIRECTION (d)] = NULL;
	}
      }
    }
  }

  if (cleanup)
    for (i = 0; i < FTT_CELLS; i++)
      if (!FTT_CELL_IS_DESTROYED (&(root->children->cell[i])))
	(* cleanup) (&(root->children->cell[i]), cleanup_data);
  g_free (root->children);
  root->children = NULL;

  return TRUE;
}
