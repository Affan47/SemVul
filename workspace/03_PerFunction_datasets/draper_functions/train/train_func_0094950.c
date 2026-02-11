gst_value_serialize_sample (const GValue * value)
{
  const GstStructure *info_structure;
  GstSegment *segment;
  GstBuffer *buffer;
  GstCaps *caps;
  GstSample *sample;
  GValue val = { 0, };
  gchar *info_str, *caps_str, *tmp;
  gchar *buf_str, *seg_str, *s;

  sample = g_value_get_boxed (value);

  buffer = gst_sample_get_buffer (sample);
  if (buffer) {
    g_value_init (&val, GST_TYPE_BUFFER);
    g_value_set_boxed (&val, buffer);
    buf_str = gst_value_serialize_buffer (&val);
    g_value_unset (&val);
  } else {
    buf_str = g_strdup ("None");
  }

  caps = gst_sample_get_caps (sample);
  if (caps) {
    tmp = gst_caps_to_string (caps);
    caps_str = g_base64_encode ((guchar *) tmp, strlen (tmp) + 1);
    g_strdelimit (caps_str, "=", '_');
    g_free (tmp);
  } else {
    caps_str = g_strdup ("None");
  }

  segment = gst_sample_get_segment (sample);
  if (segment) {
    g_value_init (&val, GST_TYPE_SEGMENT);
    g_value_set_boxed (&val, segment);
    tmp = gst_value_serialize_segment_internal (&val, FALSE);
    seg_str = g_base64_encode ((guchar *) tmp, strlen (tmp) + 1);
    g_strdelimit (seg_str, "=", '_');
    g_free (tmp);
    g_value_unset (&val);
  } else {
    seg_str = g_strdup ("None");
  }

  info_structure = gst_sample_get_info (sample);
  if (info_structure) {
    tmp = gst_structure_to_string (info_structure);
    info_str = g_base64_encode ((guchar *) tmp, strlen (tmp) + 1);
    g_strdelimit (info_str, "=", '_');
    g_free (tmp);
  } else {
    info_str = g_strdup ("None");
  }

  s = g_strconcat (buf_str, ":", caps_str, ":", seg_str, ":", info_str, NULL);
  g_free (buf_str);
  g_free (caps_str);
  g_free (seg_str);
  g_free (info_str);

  return s;
}
