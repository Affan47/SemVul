lon_lat_face_scale_metric (const GfsDomain * domain, const FttCellFace * face,
					  FttComponent c)
{
  if (c != FTT_X)
    return 1.;
  return gfs_face_interpolated_value (face, GFS_VARIABLE1 (domain->metric_data)->i);
}
