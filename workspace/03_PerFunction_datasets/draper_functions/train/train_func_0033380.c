free_gap (Gap * gap)
{
  GESTrack *track = gap->track;

  GST_DEBUG_OBJECT (track, "Removed gap with start %" GST_TIME_FORMAT
      " duration %" GST_TIME_FORMAT, GST_TIME_ARGS (gap->start),
      GST_TIME_ARGS (gap->duration));
  gst_bin_remove (GST_BIN (track->priv->composition), gap->gnlobj);
  gst_element_set_state (gap->gnlobj, GST_STATE_NULL);
  gst_object_unref (gap->gnlobj);

  g_slice_free (Gap, gap);
}
