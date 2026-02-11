compute_allocation_for_child (ClutterGridRequest *request,
                              ClutterActor       *child,
                              ClutterOrientation  orientation)
{
  ClutterGridLayoutPrivate *priv = request->grid->priv;
  ClutterGridChild *grid_child;
  ClutterGridLineData *linedata;
  ClutterGridLines *lines;
  ClutterGridLine *line;
  ClutterGridAttach *attach;
  gfloat size;
  gint i;

  grid_child = GET_GRID_CHILD (request->grid, child);
  linedata = &priv->linedata[orientation];
  lines = &request->lines[orientation];
  attach = &grid_child->attach[orientation];

  size = (attach->span - 1) * linedata->spacing;
  for (i = 0; i < attach->span; i++)
    {
      line = &lines->lines[attach->pos - lines->min + i];
      size += line->allocation;
    }

  return size;
}
