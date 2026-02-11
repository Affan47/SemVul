gst_h264_parser_identify_nalu (GstH264NalParser * nalparser,
    const guint8 * data, guint offset, gsize size, GstH264NalUnit * nalu)
{
  GstH264ParserResult res;
  gint off2;

  res =
      gst_h264_parser_identify_nalu_unchecked (nalparser, data, offset, size,
      nalu);

  if (res != GST_H264_PARSER_OK || nalu->size == 0)
    goto beach;

  off2 = scan_for_start_codes (data + nalu->offset, size - nalu->offset);
  if (off2 < 0) {
    GST_DEBUG ("Nal start %d, No end found", nalu->offset);

    return GST_H264_PARSER_NO_NAL_END;
  }

  if (off2 > 0 && data[nalu->offset + off2 - 1] == 00)
    off2--;

  nalu->size = off2;
  if (nalu->size < 2)
    return GST_H264_PARSER_BROKEN_DATA;

  GST_DEBUG ("Complete nal found. Off: %d, Size: %d", nalu->offset, nalu->size);

beach:
  return res;
}
