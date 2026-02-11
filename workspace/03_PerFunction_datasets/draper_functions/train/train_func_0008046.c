gst_frame_positionner_update_properties (GstFramePositionner * pos)
{
  GstCaps *caps;
  gint final_width;
  gint final_height;

  if (pos->capsfilter == NULL)
    return;

  final_width = (pos->width > 0) ? pos->width : pos->track_width;
  final_height = (pos->height > 0) ? pos->height : pos->track_height;

  if (final_width == 0 && final_height == 0)
    caps = gst_caps_new_empty_simple ("video/x-raw");
  else if (final_width == 0)
    caps =
        gst_caps_new_simple ("video/x-raw", "height", G_TYPE_INT, final_height,
        NULL);
  else if (final_height == 0)
    caps =
        gst_caps_new_simple ("video/x-raw", "width", G_TYPE_INT, final_width,
        NULL);
  else
    caps =
        gst_caps_new_simple ("video/x-raw", "width", G_TYPE_INT,
        final_width, "height", G_TYPE_INT, final_height, NULL);

  GST_DEBUG_OBJECT (pos, "updated size to : %d %d", final_width, final_height);

  if (pos->fps_n != -1)
    gst_caps_set_simple (caps, "framerate", GST_TYPE_FRACTION, pos->fps_n,
        pos->fps_d, NULL);

  GST_DEBUG_OBJECT (pos, "setting caps : %s", gst_caps_to_string (caps));

  g_object_set (pos->capsfilter, "caps", caps, NULL);

  g_object_notify (G_OBJECT (pos), "width");
  g_object_notify (G_OBJECT (pos), "height");
}
