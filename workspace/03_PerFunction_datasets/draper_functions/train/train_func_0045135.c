divergence_approx_hook (GfsDomain * domain,
				    GfsAdvectionParams * apar,
				    GfsVariable * div)
{
  DivergenceData q;
  GfsVariable ** v = gfs_domain_velocity (domain);

  q.div = div;
  for (q.c = 0; q.c < FTT_DIMENSION; q.c++) {
    gfs_domain_surface_bc (domain, v[q.c]);
    gfs_domain_traverse_mixed (domain, FTT_PRE_ORDER, FTT_TRAVERSE_LEAFS,
			       (FttCellTraverseFunc) moving_divergence_approx, &q);
  }
  gfs_domain_traverse_merged (domain, (GfsMergedTraverseFunc) moving_divergence_distribution, &q);
}
