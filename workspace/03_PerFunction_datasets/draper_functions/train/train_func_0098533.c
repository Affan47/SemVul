gst_video_parse_caps_color_matrix (GstCaps * caps)
{
  GstStructure *structure;
  const char *s;

  if (!gst_caps_is_fixed (caps))
    return NULL;

  structure = gst_caps_get_structure (caps, 0);

  s = gst_structure_get_string (structure, "color-matrix");
  if (s)
    return s;

  if (gst_structure_has_name (structure, "video/x-raw-yuv")) {
    return "sdtv";
  }

  return NULL;
}
