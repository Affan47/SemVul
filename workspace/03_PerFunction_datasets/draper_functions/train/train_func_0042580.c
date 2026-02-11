gst_video_parse_caps_palette (GstCaps * caps)
{
  GstStructure *s;
  const GValue *p_v;
  GstBuffer *p;

  if (!gst_caps_is_fixed (caps))
    return NULL;

  s = gst_caps_get_structure (caps, 0);

  p_v = gst_structure_get_value (s, "palette_data");
  if (!p_v || !GST_VALUE_HOLDS_BUFFER (p_v))
    return NULL;

  p = gst_buffer_ref (gst_value_get_buffer (p_v));

  return p;
}
