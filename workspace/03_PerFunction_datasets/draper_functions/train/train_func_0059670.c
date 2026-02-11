ftt_cell_point_distance2_internal (FttCell * root,
					GtsPoint * p,
					gdouble d,
					gdouble (* distance2) (FttCell *, GtsPoint *, gpointer),
					gpointer data,
					FttCell ** closest,
					gdouble * dmin)
{
  if (FTT_CELL_IS_LEAF (root)) {
    if (d < *dmin) {
      *dmin = d;
      if (closest)
	*closest = root;
    }
  }
  else {
    FttCellChildren child;
    gdouble dc[FTT_CELLS];
    guint i;

    ftt_cell_children (root, &child);
    for (i = 0; i < FTT_CELLS; i++)
      dc[i] = child.c[i] ? (* distance2) (child.c[i], p, data) : G_MAXDOUBLE;
    bubble_sort (&child, dc);
    for (i = 0; i < FTT_CELLS; i++)
      if (dc[i] < *dmin)
	ftt_cell_point_distance2_internal (child.c[i], p, dc[i], distance2, data, closest, dmin);
  }
}
