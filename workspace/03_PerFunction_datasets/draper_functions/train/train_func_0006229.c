gfs_surface_point_is_inside (GfsGenericSurface * s,
				  FttVector * p)
{
  g_return_val_if_fail (s != NULL, 0);
  g_return_val_if_fail (p != NULL, 0);

  g_assert (GFS_GENERIC_SURFACE_CLASS (GTS_OBJECT (s)->klass)->point_is_inside);
  return (* GFS_GENERIC_SURFACE_CLASS (GTS_OBJECT (s)->klass)->point_is_inside) (s, p);
}
