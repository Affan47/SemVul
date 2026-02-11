clutter_grid_request_allocate (ClutterGridRequest *request,
                               ClutterOrientation  orientation,
                               gfloat              total_size)
{
  ClutterGridLayoutPrivate *priv = request->grid->priv;
  ClutterGridLineData *linedata;
  ClutterGridLines *lines;
  ClutterGridLine *line;
  gint nonempty;
  gint expand;
  gint i, j;
  RequestedSize *sizes;
  gint extra;
  gint rest;
  gint size;

  clutter_grid_request_compute_expand (request, orientation, &nonempty, &expand);

  if (nonempty == 0)
    return;

  linedata = &priv->linedata[orientation];
  lines = &request->lines[orientation];

  size = total_size - (nonempty - 1) * linedata->spacing;

  if (linedata->homogeneous)
    {
      extra = size / nonempty;
      rest = size % nonempty;

      for (i = 0; i < lines->max - lines->min; i++)
        {
          line = &lines->lines[i];
          if (line->empty)
            continue;

          line->allocation = extra;
          if (rest > 0)
            {
              line->allocation += 1;
              rest -= 1;
            }
        }
    }
  else
    {
      sizes = g_newa (RequestedSize, nonempty);

      j = 0;
      for (i = 0; i < lines->max - lines->min; i++)
        {
          line = &lines->lines[i];
          if (line->empty)
            continue;

          size -= line->minimum;

          sizes[j].minimum_size = line->minimum;
          sizes[j].natural_size = line->natural;
          sizes[j].data = line;
          j++;
        }

      size = distribute_natural_allocation (MAX (0, size), nonempty, sizes);

      if (expand > 0)
        {
          extra = size / expand;
          rest = size % expand;
        }
      else
        {
          extra = 0;
          rest = 0;
        }

      j = 0;
      for (i = 0; i < lines->max - lines->min; i++)
        {
          line = &lines->lines[i];
          if (line->empty)
            continue;

          g_assert (line == sizes[j].data);

          line->allocation = sizes[j].minimum_size;
          if (line->expand)
            {
              line->allocation += extra;
              if (rest > 0)
                {
                  line->allocation += 1;
                  rest -= 1;
                }
            }

          j++;
        }
    }
}
