gfs_boundary_new (GfsBoundaryClass * klass,
				GfsBox * box,
				FttDirection d)
{
  GfsBoundary * boundary;

  g_return_val_if_fail (box != NULL, NULL);
  g_return_val_if_fail (d < FTT_NEIGHBORS, NULL);
  g_return_val_if_fail (box->neighbor[d] == NULL, NULL);

  boundary = GFS_BOUNDARY (gts_object_new (GTS_OBJECT_CLASS (klass)));
  boundary->box = box;
  box->neighbor[d] = GTS_OBJECT (boundary);
  boundary->d = FTT_OPPOSITE_DIRECTION (d);
  if (box->root)
    boundary_match (boundary);

  return boundary;
}
