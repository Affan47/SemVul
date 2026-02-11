create_window (GstBus * bus, GstMessage * message, GstPipeline * pipeline)
{
  GstVideoOverlay *ov = NULL;

  if (!gst_is_video_overlay_prepare_window_handle_message (message))
    return GST_BUS_PASS;

  ov = GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message));

  g_print ("Creating our own window\n");

  cycle_window (ov);

  g_timeout_add (50, (GSourceFunc) resize_window, pipeline);
  g_timeout_add (50, (GSourceFunc) move_window, pipeline);
  g_timeout_add (100, (GSourceFunc) cycle_window, ov);
  g_timeout_add_seconds (2, (GSourceFunc) toggle_events, ov);

  gst_message_unref (message);
  return GST_BUS_DROP;
}
