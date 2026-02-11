gst_h264_parser_parse_sei (GstH264NalParser * nalparser, GstH264NalUnit * nalu,
    GArray ** messages)
{
  NalReader nr;
  GstH264SEIMessage sei;
  GstH264ParserResult res;

  GST_DEBUG ("parsing SEI nal");
  nal_reader_init (&nr, nalu->data + nalu->offset + 1, nalu->size - 1);
  *messages = g_array_new (FALSE, FALSE, sizeof (GstH264SEIMessage));

  do {
    res = gst_h264_parser_parse_sei_message (nalparser, &nr, &sei);
    if (res == GST_H264_PARSER_OK)
      g_array_append_val (*messages, sei);
    else
      break;
  } while (gst_h264_parser_more_data (&nr));

  return res;
}
