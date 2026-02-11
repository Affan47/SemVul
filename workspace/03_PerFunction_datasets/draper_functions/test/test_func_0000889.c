closest_box_grid_new (FttVector min, FttVector max,
					   gdouble h)
{
  ClosestGrid * g = g_malloc (sizeof (ClosestGrid));
  guint i;

  g->max = max;
  g->min = min;
  g->nx = (g->max.x - g->min.x)/h + 3;
  g->h = h;
  g->ny = (g->max.y - g->min.y)/h + 3;
  g->min.x -= h;
  g->min.y -= h;
  g->max.x = g->min.x + g->nx*g->h;
  g->max.y = g->min.y + g->ny*g->h;
  g->p = g_malloc (g->nx*sizeof (GSList **));
  for (i = 0; i < g->nx; i++)
    g->p[i] = g_malloc0 (g->ny*sizeof (GSList *));

  return g;
}
