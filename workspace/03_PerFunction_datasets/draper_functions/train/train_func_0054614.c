gst_video_format_new_template_caps (GstVideoFormat format)
{
  GstCaps *caps;
  GstStructure *structure;

  g_return_val_if_fail (format != GST_VIDEO_FORMAT_UNKNOWN, NULL);

  caps = gst_video_format_new_caps_raw (format);
  if (caps) {
    GValue value = { 0 };
    GValue v = { 0 };

    structure = gst_caps_get_structure (caps, 0);

    gst_structure_set (structure,
        "width", GST_TYPE_INT_RANGE, 1, G_MAXINT,
        "height", GST_TYPE_INT_RANGE, 1, G_MAXINT,
        "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1,
        "pixel-aspect-ratio", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);

    g_value_init (&value, GST_TYPE_LIST);
    g_value_init (&v, G_TYPE_BOOLEAN);
    g_value_set_boolean (&v, TRUE);
    gst_value_list_append_value (&value, &v);
    g_value_set_boolean (&v, FALSE);
    gst_value_list_append_value (&value, &v);
    g_value_unset (&v);

    gst_structure_take_value (structure, "interlaced", &value);
  }

  return caps;
}
