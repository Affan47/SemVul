gst_mpeg2dec_sink_convert (GstPad * pad, GstFormat src_format, gint64 src_value,
    GstFormat * dest_format, gint64 * dest_value)
{
  gboolean res = TRUE;
  GstMpeg2dec *mpeg2dec;
  const mpeg2_info_t *info;

  mpeg2dec = GST_MPEG2DEC (GST_PAD_PARENT (pad));

  if (mpeg2dec->decoder == NULL)
    return FALSE;

  if (src_format == *dest_format) {
    *dest_value = src_value;
    return TRUE;
  }

  info = mpeg2_info (mpeg2dec->decoder);

  switch (src_format) {
    case GST_FORMAT_BYTES:
      switch (*dest_format) {
        case GST_FORMAT_TIME:
          if (info->sequence && info->sequence->byte_rate) {
            *dest_value =
                gst_util_uint64_scale (GST_SECOND, src_value,
                info->sequence->byte_rate);
            GST_WARNING_OBJECT (mpeg2dec, "dest_value:%" GST_TIME_FORMAT,
                GST_TIME_ARGS (*dest_value));
            break;
          } else if (info->sequence)
            GST_WARNING_OBJECT (mpeg2dec,
                "Cannot convert from BYTES to TIME since we don't know the bitrate at this point.");
        default:
          res = FALSE;
      }
      break;
    case GST_FORMAT_TIME:
      switch (*dest_format) {
        case GST_FORMAT_BYTES:
          if (info->sequence && info->sequence->byte_rate) {
            *dest_value =
                gst_util_uint64_scale_int (src_value, info->sequence->byte_rate,
                GST_SECOND);
            break;
          } else if (info->sequence)
            GST_WARNING_OBJECT (mpeg2dec,
                "Cannot convert from TIME to BYTES since we don't know the bitrate at this point.");
        default:
          res = FALSE;
      }
      break;
    default:
      res = FALSE;
  }
  return res;
}
