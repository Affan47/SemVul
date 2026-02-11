gfs_domain_cell_traverse_box (GfsDomain * domain,
				   GtsBBox * box,
				   FttTraverseType order,
				   FttTraverseFlags flags,
				   gint max_depth,
				   FttCellTraverseFunc func,
				   gpointer data)
{
  gpointer datum[6];

  datum[0] = &order;
  datum[1] = &flags;
  datum[2] = &max_depth;
  datum[3] = func;
  datum[4] = data;
  datum[5] = box;

  g_return_if_fail (domain != NULL);
  g_return_if_fail (box != NULL);
  g_return_if_fail (func != NULL);

  gts_container_foreach (GTS_CONTAINER (domain),
			 (GtsFunc) box_traverse_box, datum);
}
