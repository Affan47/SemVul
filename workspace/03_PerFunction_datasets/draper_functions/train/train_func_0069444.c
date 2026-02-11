lon_lat_scale_metric (const GfsDomain * domain, const FttCell * cell, FttComponent c)
{
  if (c != FTT_X)
    return 1.;
  return GFS_VALUE (cell, GFS_VARIABLE1 (domain->metric_data));
}
