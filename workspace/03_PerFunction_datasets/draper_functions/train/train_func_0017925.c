solid_curvature (FttCell * cell, FttCellFace * face,
				GfsDomain * domain, GfsGenericSurface * s)
{
  KappaData d;
  d.kappa = gfs_solid_is_thin (cell, s) ? 1./ftt_cell_size (cell) : 0.;
  d.s = GFS_SURFACE (s)->s;
  gts_surface_foreach_vertex (d.s, (GtsFunc) max_kappa, &d);
  return d.kappa;
}
