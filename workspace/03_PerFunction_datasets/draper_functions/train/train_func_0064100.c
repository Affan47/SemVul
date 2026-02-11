gfs_domain_homogeneous_bc (GfsDomain * domain,
				FttTraverseFlags flags,
				gint max_depth,
				GfsVariable * ov,
				GfsVariable * v)
{
  BcData b = { flags, max_depth, v, ov, FTT_XYZ};

  g_return_if_fail (domain != NULL);
  g_return_if_fail (ov != NULL);
  g_return_if_fail (v != NULL);

  if (domain->profile_bc)
    gfs_domain_timer_start (domain, "bc");

  gts_container_foreach (GTS_CONTAINER (domain), (GtsFunc) box_homogeneous_bc, &b);
  gts_container_foreach (GTS_CONTAINER (domain), (GtsFunc) box_receive_bc, &b);
  gts_container_foreach (GTS_CONTAINER (domain), (GtsFunc) box_synchronize, &b.c);

  if (domain->profile_bc)
    gfs_domain_timer_stop (domain, "bc");
}
