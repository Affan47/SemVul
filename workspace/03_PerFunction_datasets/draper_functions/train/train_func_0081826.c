gfs_isosurface (GfsDomain * domain,
			     GfsVariable * v, gdouble val,
			     gint level)
{
  FttVector cmax = { - G_MAXDOUBLE, - G_MAXDOUBLE, - G_MAXDOUBLE };
  FttVector cmin = { G_MAXDOUBLE, G_MAXDOUBLE, G_MAXDOUBLE };
  guint depth;
  GtsCartesianGrid g;
  gpointer data[3];
  GtsSurface * s;

  g_return_val_if_fail (domain != NULL, NULL);
  g_return_val_if_fail (v != NULL, NULL);

  if (level < 0)
    depth = gfs_domain_depth (domain);
  else
    depth = level;

  data[0] = &cmin;
  data[1] = &cmax;
  gfs_domain_cell_traverse (domain, FTT_PRE_ORDER,
			    FTT_TRAVERSE_LEAFS|FTT_TRAVERSE_LEVEL, depth,
			    (FttCellTraverseFunc) extent, data);
  if (cmin.x == G_MAXDOUBLE)
    return NULL;

  g.dx = g.dy = g.dz = ftt_level_size (depth);
  g.x = cmin.x; g.y = cmin.y; g.z = cmin.z;
  g.nx = (cmax.x - cmin.x)/g.dx + 1;
  g.ny = (cmax.y - cmin.y)/g.dy + 1;
  g.nz = (cmax.z - cmin.z)/g.dz + 1;

  s = gts_surface_new (gts_surface_class (),
		       gts_face_class (),
		       gts_edge_class (),
		       gts_vertex_class ());
  data[0] = domain;
  data[1] = &depth;
  data[2] = v;
  gts_isosurface_cartesian (s, g, (GtsIsoCartesianFunc) iso_func, data, val);

  return s;
}
