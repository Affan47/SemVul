gst_video_overlay_prepare_window_handle (GstVideoOverlay * overlay)
{
  GstStructure *s;
  GstMessage *msg;

  g_return_if_fail (overlay != NULL);
  g_return_if_fail (GST_IS_VIDEO_OVERLAY (overlay));

  GST_LOG_OBJECT (GST_OBJECT (overlay), "prepare window handle");
  s = gst_structure_new_empty ("prepare-window-handle");
  msg = gst_message_new_element (GST_OBJECT (overlay), s);
  gst_element_post_message (GST_ELEMENT (overlay), msg);
}
