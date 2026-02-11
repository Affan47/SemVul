gst_face_overlay_create_children (GstFaceOverlay * filter)
{
  gboolean ret = TRUE;

  if ((filter->colorspace = gst_element_factory_make ("ffmpegcolorspace",
              NULL)) == NULL) {
    return FALSE;
  }

  if ((filter->face_detect = gst_element_factory_make ("facedetect",
              NULL)) == NULL) {
    return FALSE;
  }
  g_object_set (filter->face_detect, "display", 0, NULL);

  if ((filter->svg_overlay = gst_element_factory_make ("rsvgoverlay",
              NULL)) == NULL) {
    return FALSE;
  }

  gst_bin_add_many (GST_BIN (filter),
      filter->face_detect, filter->colorspace, filter->svg_overlay, NULL);

  ret &= gst_element_link_pads (filter->face_detect, "src",
      filter->colorspace, "sink");
  ret &= gst_element_link_pads (filter->colorspace, "src",
      filter->svg_overlay, "sink");

  ret &= gst_face_overlay_create_pad (filter, filter->sinkpad, "sink",
      filter->face_detect);
  ret &= gst_face_overlay_create_pad (filter, filter->srcpad, "src",
      filter->svg_overlay);

  return ret;

}
