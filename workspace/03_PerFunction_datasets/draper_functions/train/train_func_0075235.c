box_match (GfsBox * box)
{
  FttDirection d;

  for (d = 0; d < FTT_NEIGHBORS; d++)
    if (GFS_IS_BOUNDARY (box->neighbor[d])) {
      GfsBoundary * boundary = GFS_BOUNDARY (box->neighbor[d]);

      g_assert (GFS_BOUNDARY_CLASS (box->neighbor[d]->klass)->match);
      boundary->type = GFS_BOUNDARY_MATCH_VARIABLE;
      (* GFS_BOUNDARY_CLASS (box->neighbor[d]->klass)->match) (boundary);
      if (!boundary->root) {
	gts_object_destroy (GTS_OBJECT (boundary));
	box->neighbor[d] = NULL;
      }
      else
	gfs_boundary_send (boundary);
    }
}
