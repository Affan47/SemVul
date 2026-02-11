gfs_domain_stats_variable (GfsDomain * domain,
				    GfsVariable * v,
				    FttTraverseFlags flags,
				    gint max_depth,
				    gboolean (* condition) (FttCell *, gpointer),
				    gpointer cdata)
{
  GtsRange s;
  gpointer data[2];

  g_return_val_if_fail (domain != NULL, s);
  g_return_val_if_fail (v != NULL, s);

  gts_range_init (&s);
  data[0] = &s;
  data[1] = v;
  if (condition)
    gfs_domain_cell_traverse_condition (domain, FTT_PRE_ORDER, flags, max_depth,
					(FttCellTraverseFunc) add_stats, data,
					condition, cdata);
  else
    gfs_domain_cell_traverse (domain, FTT_PRE_ORDER, flags, max_depth,
			      (FttCellTraverseFunc) add_stats, data);
  domain_range_reduce (domain, &s);
  gts_range_update (&s);

  return s;
}
