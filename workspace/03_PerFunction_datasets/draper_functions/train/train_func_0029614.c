gst_video_test_src_parse_caps (const GstCaps * caps,
    gint * width, gint * height, gint * fps_n, gint * fps_d,
    GstVideoColorimetry * colorimetry, gint * x_inv, gint * y_inv)
{
  const GstStructure *structure;
  GstPadLinkReturn ret;
  const GValue *framerate;
  const gchar *str;

  GST_DEBUG ("parsing caps");

  structure = gst_caps_get_structure (caps, 0);

  ret = gst_structure_get_int (structure, "width", width);
  ret &= gst_structure_get_int (structure, "height", height);
  framerate = gst_structure_get_value (structure, "framerate");

  if (framerate) {
    *fps_n = gst_value_get_fraction_numerator (framerate);
    *fps_d = gst_value_get_fraction_denominator (framerate);
  } else
    goto no_framerate;

  if ((str = gst_structure_get_string (structure, "colorimetry")))
    gst_video_colorimetry_from_string (colorimetry, str);

  if ((str = gst_structure_get_string (structure, "format"))) {
    if (g_str_equal (str, "bggr")) {
      *x_inv = *y_inv = 0;
    } else if (g_str_equal (str, "rggb")) {
      *x_inv = *y_inv = 1;
    } else if (g_str_equal (str, "grbg")) {
      *x_inv = 0;
      *y_inv = 1;
    } else if (g_str_equal (str, "grbg")) {
      *x_inv = 1;
      *y_inv = 0;
    } else
      goto invalid_format;
  }
  return ret;


no_framerate:
  {
    GST_DEBUG ("videotestsrc no framerate given");
    return FALSE;
  }
invalid_format:
  {
    GST_DEBUG ("videotestsrc invalid bayer format given");
    return FALSE;
  }
}
