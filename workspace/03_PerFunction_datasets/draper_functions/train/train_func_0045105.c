gfs_source_friction_saved_value (GfsSourceGeneric * s,
						FttCell * cell,
						GfsVariable * v)
{
  gdouble H = GFS_VARIABLE (cell, GFS_SOURCE_FRICTION (s)->h->i);

  g_assert (H > 0.);
  return - GFS_SOURCE_FRICTION (s)->f*
    GFS_VARIABLE (cell, GFS_SOURCE_FRICTION (s)->u[v->component]->i)/H;
}
