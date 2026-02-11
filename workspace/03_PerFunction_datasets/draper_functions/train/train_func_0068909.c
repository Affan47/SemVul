bvw_set_playback_direction (BaconVideoWidget *bvw, gboolean forward)
{
  gboolean is_forward;
  gboolean retval;

  is_forward = (bvw->priv->rate > 0.0);
  if (forward == is_forward)
    return TRUE;

  retval = FALSE;

  if (forward == FALSE) {
    GstEvent *event;
    gint64 cur = 0;

    if (gst_element_query_position (bvw->priv->play, GST_FORMAT_TIME, &cur)) {
      GST_DEBUG ("Setting playback direction to reverse at %"G_GINT64_FORMAT"", cur);
      event = gst_event_new_seek (REVERSE_RATE,
				  GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,
				  GST_SEEK_TYPE_SET, G_GINT64_CONSTANT (0),
				  GST_SEEK_TYPE_SET, cur);
      if (gst_element_send_event (bvw->priv->play, event) == FALSE) {
	GST_WARNING ("Failed to set playback direction to reverse");
      } else {
	gst_element_get_state (bvw->priv->play, NULL, NULL, GST_CLOCK_TIME_NONE);
	bvw->priv->rate = REVERSE_RATE;
	retval = TRUE;
      }
    } else {
      GST_LOG ("Failed to query position to set playback to reverse");
    }
  } else {
    GstEvent *event;
    gint64 cur = 0;

    cur = 0;
    if (gst_element_query_position (bvw->priv->play, GST_FORMAT_TIME, &cur)) {
      GST_DEBUG ("Setting playback direction to forward at %"G_GINT64_FORMAT"", cur);
      event = gst_event_new_seek (FORWARD_RATE,
				  GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,
				  GST_SEEK_TYPE_SET, cur,
				  GST_SEEK_TYPE_SET, G_GINT64_CONSTANT (0));
      if (gst_element_send_event (bvw->priv->play, event) == FALSE) {
	GST_WARNING ("Failed to set playback direction to forward");
      } else {
	gst_element_get_state (bvw->priv->play, NULL, NULL, GST_CLOCK_TIME_NONE);
	bvw->priv->rate = FORWARD_RATE;
	retval = TRUE;
      }
    } else {
      GST_LOG ("Failed to query position to set playback to forward");
    }
  }

  return retval;
}
