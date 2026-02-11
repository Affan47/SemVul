gst_h264_parser_parse_sps (GstH264NalParser * nalparser, GstH264NalUnit * nalu,
    GstH264SPS * sps, gboolean parse_vui_params)
{
  GstH264ParserResult res = gst_h264_parse_sps (nalu, sps, parse_vui_params);

  if (res == GST_H264_PARSER_OK) {
    GST_DEBUG ("adding sequence parameter set with id: %d to array", sps->id);

    nalparser->sps[sps->id] = *sps;
    nalparser->last_sps = &nalparser->sps[sps->id];
  }


  return res;
}
