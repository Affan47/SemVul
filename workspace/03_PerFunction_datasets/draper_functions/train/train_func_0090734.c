gst_x_overlay_got_window_handle (GstXOverlay * overlay, guintptr handle)
{
  GstStructure *s;
  GstMessage *msg;

  g_return_if_fail (overlay != NULL);
  g_return_if_fail (GST_IS_X_OVERLAY (overlay));

  GST_LOG_OBJECT (GST_OBJECT (overlay), "xwindow_id = %p", (gpointer)
      handle);
  s = gst_structure_new ("have-xwindow-id",
      "xwindow-id", G_TYPE_ULONG, (unsigned long) handle,
      "window-handle", G_TYPE_UINT64, (guint64) handle, NULL);
  msg = gst_message_new_element (GST_OBJECT (overlay), s);
  gst_element_post_message (GST_ELEMENT (overlay), msg);
}
