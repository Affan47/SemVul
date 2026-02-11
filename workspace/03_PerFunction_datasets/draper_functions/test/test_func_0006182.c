gfs_domain_cfl (GfsDomain * domain,
			FttTraverseFlags flags,
			gint max_depth)
{
  CflData p;

  g_return_val_if_fail (domain != NULL, 0.);

  p.cfl = G_MAXDOUBLE;
  p.v = gfs_domain_velocity (domain);
  p.domain = domain;
  gfs_domain_face_traverse (domain, FTT_XYZ, FTT_PRE_ORDER, flags, max_depth,
			    (FttFaceTraverseFunc) minimum_mac_cfl, &p);
  gfs_domain_cell_traverse (domain, FTT_PRE_ORDER, flags, max_depth,
			    (FttCellTraverseFunc) minimum_cfl, &p);
  gfs_all_reduce (domain, p.cfl, MPI_DOUBLE, MPI_MIN);
  return sqrt (p.cfl);
}
