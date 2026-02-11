gst_aac_parse_check_valid_frame (GstBaseParse * parse,
    GstBaseParseFrame * frame, guint * framesize, gint * skipsize)
{
  const guint8 *data;
  GstAacParse *aacparse;
  gboolean ret = FALSE;
  gboolean lost_sync;
  GstBuffer *buffer;

  aacparse = GST_AAC_PARSE (parse);
  buffer = frame->buffer;
  data = GST_BUFFER_DATA (buffer);

  lost_sync = GST_BASE_PARSE_LOST_SYNC (parse);

  if (aacparse->header_type == DSPAAC_HEADER_ADIF ||
      aacparse->header_type == DSPAAC_HEADER_NONE) {

    *framesize = GST_BUFFER_SIZE (buffer);
    ret = TRUE;

  } else if (aacparse->header_type == DSPAAC_HEADER_NOT_PARSED || lost_sync) {

    ret = gst_aac_parse_detect_stream (aacparse, data, GST_BUFFER_SIZE (buffer),
        GST_BASE_PARSE_DRAINING (parse), framesize, skipsize);

  } else if (aacparse->header_type == DSPAAC_HEADER_ADTS) {
    guint needed_data = 1024;

    ret = gst_aac_parse_check_adts_frame (aacparse, data,
        GST_BUFFER_SIZE (buffer), GST_BASE_PARSE_DRAINING (parse),
        framesize, &needed_data);

    if (!ret) {
      GST_DEBUG ("buffer didn't contain valid frame");
      gst_base_parse_set_min_frame_size (GST_BASE_PARSE (aacparse),
          needed_data);
    }

  } else {
    GST_DEBUG ("buffer didn't contain valid frame");
    gst_base_parse_set_min_frame_size (GST_BASE_PARSE (aacparse),
        ADTS_MAX_SIZE);
  }

  return ret;
}
