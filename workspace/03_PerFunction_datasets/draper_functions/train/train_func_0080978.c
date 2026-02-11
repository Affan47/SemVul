gst_h264_parser_identify_nalu_unchecked (GstH264NalParser * nalparser,
    const guint8 * data, guint offset, gsize size, GstH264NalUnit * nalu)
{
  gint off1;

  if (size < offset + 4) {
    GST_DEBUG ("Can't parse, buffer has too small size %" G_GSIZE_FORMAT
        ", offset %u", size, offset);
    return GST_H264_PARSER_ERROR;
  }

  off1 = scan_for_start_codes (data + offset, size - offset);

  if (off1 < 0) {
    GST_DEBUG ("No start code prefix in this buffer");
    return GST_H264_PARSER_NO_NAL;
  }

  if (offset + off1 == size - 1) {
    GST_DEBUG ("Missing data to identify nal unit");

    return GST_H264_PARSER_ERROR;
  }

  nalu->valid = TRUE;
  nalu->sc_offset = offset + off1;


  if (nalu->sc_offset > 0 && data[nalu->sc_offset - 1] == 00)
    nalu->sc_offset--;

  nalu->offset = offset + off1 + 3;
  nalu->data = (guint8 *) data;

  set_nalu_datas (nalu);

  if (nalu->type == GST_H264_NAL_SEQ_END ||
      nalu->type == GST_H264_NAL_STREAM_END) {
    GST_DEBUG ("end-of-seq or end-of-stream nal found");
    nalu->size = 0;
    return GST_H264_PARSER_OK;
  }

  nalu->size = size - nalu->offset;

  return GST_H264_PARSER_OK;
}
