gst_x_overlay_prepare_xwindow_id (GstXOverlay * overlay)
{
  GstStructure *s;
  GstMessage *msg;

  g_return_if_fail (overlay != NULL);
  g_return_if_fail (GST_IS_X_OVERLAY (overlay));

  GST_LOG_OBJECT (GST_OBJECT (overlay), "prepare xwindow_id");
  s = gst_structure_new ("prepare-xwindow-id", NULL);
  msg = gst_message_new_element (GST_OBJECT (overlay), s);
  gst_element_post_message (GST_ELEMENT (overlay), msg);
}
