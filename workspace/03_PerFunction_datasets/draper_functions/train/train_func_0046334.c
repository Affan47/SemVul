gst_inter_video_src_fixate (GstBaseSrc * src, GstCaps * caps)
{
  GstInterVideoSrc *intervideosrc = GST_INTER_VIDEO_SRC (src);
  GstStructure *structure;

  GST_DEBUG_OBJECT (intervideosrc, "fixate");

  structure = gst_caps_get_structure (caps, 0);

  gst_structure_fixate_field_nearest_int (structure, "width", 320);
  gst_structure_fixate_field_nearest_int (structure, "height", 240);
  gst_structure_fixate_field_nearest_fraction (structure, "framerate", 30, 1);
  if (gst_structure_has_field (structure, "pixel-aspect-ratio"))
    gst_structure_fixate_field_nearest_fraction (structure,
        "pixel-aspect-ratio", 1, 1);
  if (gst_structure_has_field (structure, "color-matrix"))
    gst_structure_fixate_field_string (structure, "color-matrix", "sdtv");
  if (gst_structure_has_field (structure, "chroma-site"))
    gst_structure_fixate_field_string (structure, "chroma-site", "mpeg2");

  if (gst_structure_has_field (structure, "interlaced"))
    gst_structure_fixate_field_boolean (structure, "interlaced", FALSE);

}
