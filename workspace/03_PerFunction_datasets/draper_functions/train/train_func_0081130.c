gfs_domain_bc (GfsDomain * domain,
		    FttTraverseFlags flags,
		    gint max_depth,
		    GfsVariable * v)
{
  g_return_if_fail (domain != NULL);
  g_return_if_fail (v != NULL);

  gfs_domain_copy_bc (domain, flags, max_depth, v, v);
}
