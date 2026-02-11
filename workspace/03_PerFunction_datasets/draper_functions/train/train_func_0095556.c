gfs_gedge_new (GfsGEdgeClass * klass,
			  GfsBox * b1, GfsBox * b2,
			  FttDirection d)
{
  GfsGEdge * edge;

  g_return_val_if_fail (klass != NULL, NULL);
  g_return_val_if_fail (b1 != NULL, NULL);
  g_return_val_if_fail (b2 != NULL, NULL);
  g_return_val_if_fail (d >= 0 && d < FTT_NEIGHBORS, NULL);

  edge = GFS_GEDGE (gts_gedge_new (GTS_GEDGE_CLASS (klass),
				   GTS_GNODE (b1), GTS_GNODE (b2)));
  edge->d = d;

  gfs_gedge_link_boxes (edge);

  return edge;
}
