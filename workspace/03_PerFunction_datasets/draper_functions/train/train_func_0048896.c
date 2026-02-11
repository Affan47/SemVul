append_with_other_format (GstCaps * caps, GstStructure * s, gboolean isfloat)
{
  GstStructure *s2;

  if (isfloat) {
    s2 = gst_structure_copy (s);
    gst_structure_set_name (s2, "audio/x-raw-int");
    make_lossless_changes (s2, FALSE);


    strip_width_64 (s2);
    gst_caps_append_structure (caps, s2);
  } else {
    s2 = gst_structure_copy (s);
    gst_structure_set_name (s2, "audio/x-raw-float");
    make_lossless_changes (s2, TRUE);
    gst_caps_append_structure (caps, s2);
  }
}
