gst_ximagesink_navigation_send_event (GstNavigation * navigation,
    GstStructure * structure)
{
  GstXImageSink *ximagesink = GST_XIMAGESINK (navigation);
  GstEvent *event;
  gint x_offset, y_offset;
  gdouble x, y;
  GstPad *pad = NULL;

  event = gst_event_new_navigation (structure);


  g_mutex_lock (&ximagesink->flow_lock);

  if (!ximagesink->xwindow) {
    g_mutex_unlock (&ximagesink->flow_lock);
    return;
  }

  x_offset = ximagesink->xwindow->width - GST_VIDEO_SINK_WIDTH (ximagesink);
  y_offset = ximagesink->xwindow->height - GST_VIDEO_SINK_HEIGHT (ximagesink);

  g_mutex_unlock (&ximagesink->flow_lock);

  if (x_offset > 0 && gst_structure_get_double (structure, "pointer_x", &x)) {
    x -= x_offset / 2;
    gst_structure_set (structure, "pointer_x", G_TYPE_DOUBLE, x, NULL);
  }
  if (y_offset > 0 && gst_structure_get_double (structure, "pointer_y", &y)) {
    y -= y_offset / 2;
    gst_structure_set (structure, "pointer_y", G_TYPE_DOUBLE, y, NULL);
  }

  pad = gst_pad_get_peer (GST_VIDEO_SINK_PAD (ximagesink));

  if (GST_IS_PAD (pad) && GST_IS_EVENT (event)) {
    gst_pad_send_event (pad, event);

    gst_object_unref (pad);
  }
}
