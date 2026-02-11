ftt_face_traverse_boundary (FttCell * root,
				 FttDirection d,
				 FttTraverseType order,
				 FttTraverseFlags flags,
				 gint max_depth,
				 FttFaceTraverseFunc func,
				 gpointer data)
{
  gpointer datum[3];

  g_return_if_fail (root != NULL);
  g_return_if_fail (d < FTT_NEIGHBORS);
  g_return_if_fail (func != NULL);

  datum[0] = &d;
  datum[1] = func;
  datum[2] = data;
  ftt_cell_traverse_boundary (root, d, order, flags, max_depth,
			      (FttCellTraverseFunc) traverse_face_boundary,
			      datum);
}
