face_coeff_from_below (FttCell * cell)
{
  FttDirection d;
  GfsFaceStateVector * f = GFS_STATE (cell)->f;
  guint neighbors = 0;

  for (d = 0; d < FTT_NEIGHBORS; d++) {
    FttCellChildren child;
    guint i, n;

    f[d].v = 0.;
    n = ftt_cell_children_direction (cell, d, &child);
    for (i = 0; i < n; i++)
      if (child.c[i])
	f[d].v += GFS_STATE (child.c[i])->f[d].v;
    f[d].v /= n;

    FttCell * neighbor;
    if (f[d].v > 0. && (neighbor = ftt_cell_neighbor (cell, d)) && !GFS_CELL_IS_BOUNDARY (neighbor))
      neighbors++;
  }

  if (neighbors == 1)
    for (d = 0; d < FTT_NEIGHBORS; d++)
      f[d].v = 0.;
}
