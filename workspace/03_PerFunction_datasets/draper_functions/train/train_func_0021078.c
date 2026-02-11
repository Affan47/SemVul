gfs_cell_corner_interpolator (FttCell * cell,
				   FttDirection d[FTT_DIMENSION],
				   gint max_level,
				   gboolean centered,
				   GfsInterpolator * inter)
{
  FttCell * n[N_CELLS];
  guint i;
  gboolean t_junction;

  g_return_if_fail (cell != NULL);
  g_return_if_fail (inter != NULL);

  while (!FTT_CELL_IS_LEAF (cell) &&
	 ftt_cell_level (cell) != max_level &&
	 (n[0] = ftt_cell_child_corner (cell, d)))
    cell = n[0];
  n[0] = cell;
  for (i = 1; i < N_CELLS; i++)
    n[i] = NULL;
  t_junction = do_path (cell, 0, n, d, max_level, centered, inter);
  if (t_junction)
    return;

  {
    FttVector c;
    gdouble w = 0.;

    inter->n = 0;
    ftt_corner_pos (cell, d, &c);
    for (i = 0; i < N_CELLS; i++)
      if (n[i]) {
	gdouble a;
	a = 1./(distance (&c, n[i], centered) + 1e-12);
	inter->c[inter->n] = n[i];
	inter->w[inter->n++] = a;
	w += a;
      }
    g_assert (w > 0.);
    interpolator_scale (inter, 1./w);
  }
}
