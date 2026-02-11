cell_corner_neighbor1 (FttCell * cell,
					FttDirection * d,
					gint max_level)
{
  if (!cell)
    return NULL;
  FttCell * neighbor = ftt_cell_neighbor (cell, d[0]);
  if (!neighbor)
    return NULL;
  else {
    guint level = ftt_cell_level (cell);
    if (ftt_cell_level (neighbor) < level)

      return neighbor;
    else {
      if (level == max_level || FTT_CELL_IS_LEAF (neighbor))

	return neighbor;
      else {

	guint i;
	FttDirection d1[FTT_DIMENSION];
	d1[0] = FTT_OPPOSITE_DIRECTION (d[0]);
	for (i = 1; i < FTT_DIMENSION; i++)
	  d1[i] = d[i];
	return ftt_cell_child_corner (neighbor, d1);
      }
    }
  }
}
