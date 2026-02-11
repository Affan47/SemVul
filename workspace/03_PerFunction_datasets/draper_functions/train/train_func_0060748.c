closest_grid_destroy (ClosestGrid * g)
{
  guint i, j;

  for (i = 0; i < g->nx; i++) {
    for (j = 0; j < g->ny; j++)
      g_slist_free (g->p[i][j]);
    g_free (g->p[i]);
  }
  g_free (g->p);
  g_free (g);
}
