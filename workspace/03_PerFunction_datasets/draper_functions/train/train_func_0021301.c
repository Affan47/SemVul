closest_grid_add (ClosestGrid * g, GtsPoint * p,
				      gdouble dmin, gdouble ds)
{
  InsertStatus status;
  gint i = (p->x - g->min.x)/(g->max.x - g->min.x)*g->nx;
  gint j = (p->y - g->min.y)/(g->max.y - g->min.y)*g->ny;

  if ((status = closest_grid_is_insertable (g, p, dmin, ds)) != INSERTED)
    return status;
  g->p[i][j] = g_slist_prepend (g->p[i][j], p);
  return INSERTED;
}
