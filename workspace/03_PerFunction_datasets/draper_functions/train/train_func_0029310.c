gst_mpeg4vparse_start (GstBaseParse * parse)
{
  GstMpeg4VParse *mp4vparse = GST_MPEG4VIDEO_PARSE (parse);

  GST_DEBUG_OBJECT (parse, "start");

  gst_mpeg4vparse_reset (mp4vparse);

  gst_base_parse_set_min_frame_size (parse, 6);

  return TRUE;
}
