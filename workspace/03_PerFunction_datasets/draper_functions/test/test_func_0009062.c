gfs_surface_implicit_value (GfsSurface * s, GtsPoint p)
{
  g_return_val_if_fail (s != NULL, 0.);
  g_return_val_if_fail (s->f != NULL || s->bbtree != NULL, 0.);

  if (s->f) {
    if (s->m)
      gts_point_transform (&p, s->m);
    return (s->flip ? -1. : 1.)*(gfs_function_spatial_value (s->f, (FttVector *)&p.x)
				  + 1e-6);
  }
  else {
    GtsBBox * bbox;
    gdouble d2 = gts_bb_tree_point_distance (s->bbtree, &p,
					     (GtsBBoxDistFunc) gts_point_triangle_distance2,
					     &bbox);
    return gts_point_is_inside_surface (&p, s->bbtree, TRUE) ? d2 : - d2;
  }
}
