gst_h264_parse_collect_nal (GstH264Parse * h264parse, const guint8 * data,
    guint size, GstH264NalUnit * nalu)
{
  gboolean complete;
  GstH264ParserResult parse_res;
  GstH264NalUnitType nal_type = nalu->type;
  GstH264NalUnit nnalu;

  GST_DEBUG_OBJECT (h264parse, "parsing collected nal");
  parse_res = gst_h264_parser_identify_nalu (h264parse->nalparser, data,
      nalu->offset + nalu->size, size, &nnalu);

  if (parse_res == GST_H264_PARSER_ERROR)
    return FALSE;


  GST_LOG_OBJECT (h264parse, "nal type: %d %s", nal_type, _nal_name (nal_type));


  h264parse->picture_start |= (nal_type == GST_H264_NAL_SLICE ||
      nal_type == GST_H264_NAL_SLICE_DPA || nal_type == GST_H264_NAL_SLICE_IDR);


  nal_type = nnalu.type;
  complete = h264parse->picture_start && (nal_type >= GST_H264_NAL_SEI &&
      nal_type <= GST_H264_NAL_AU_DELIMITER);

  GST_LOG_OBJECT (h264parse, "next nal type: %d %s", nal_type,
      _nal_name (nal_type));
  complete |= h264parse->picture_start && (nal_type == GST_H264_NAL_SLICE
      || nal_type == GST_H264_NAL_SLICE_DPA
      || nal_type == GST_H264_NAL_SLICE_IDR) &&

      (nnalu.data[nnalu.offset + 1] & 0x80);

  GST_LOG_OBJECT (h264parse, "au complete: %d", complete);

  return complete;
}
