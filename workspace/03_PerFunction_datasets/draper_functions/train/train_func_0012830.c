theora_parse_src_convert (GstPad * pad,
    GstFormat src_format, gint64 src_value,
    GstFormat * dest_format, gint64 * dest_value)
{
  gboolean res = TRUE;
  GstTheoraParse *parse;
  guint64 scale = 1;

  if (src_format == *dest_format) {
    *dest_value = src_value;
    return TRUE;
  }

  parse = GST_THEORA_PARSE (gst_pad_get_parent (pad));


  if (!parse->streamheader_received)
    goto no_header;

  switch (src_format) {
    case GST_FORMAT_BYTES:
      switch (*dest_format) {
        case GST_FORMAT_DEFAULT:
          *dest_value = gst_util_uint64_scale_int (src_value, 2,
              parse->info.pic_height * parse->info.pic_width * 3);
          break;
        case GST_FORMAT_TIME:

        default:
          res = FALSE;
      }
      break;
    case GST_FORMAT_TIME:
      switch (*dest_format) {
        case GST_FORMAT_BYTES:
          scale = 3 * (parse->info.pic_width * parse->info.pic_height) / 2;
        case GST_FORMAT_DEFAULT:
          *dest_value = scale * gst_util_uint64_scale (src_value,
              parse->info.fps_numerator,
              parse->info.fps_denominator * GST_SECOND);
          break;
        default:
          GST_DEBUG_OBJECT (parse, "cannot convert to format %s",
              gst_format_get_name (*dest_format));
          res = FALSE;
      }
      break;
    case GST_FORMAT_DEFAULT:
      switch (*dest_format) {
        case GST_FORMAT_TIME:
          *dest_value = gst_util_uint64_scale (src_value,
              GST_SECOND * parse->info.fps_denominator,
              parse->info.fps_numerator);
          break;
        case GST_FORMAT_BYTES:
          *dest_value = gst_util_uint64_scale_int (src_value,
              3 * parse->info.pic_width * parse->info.pic_height, 2);
          break;
        default:
          res = FALSE;
      }
      break;
    default:
      res = FALSE;
  }
done:
  gst_object_unref (parse);
  return res;


no_header:
  {
    GST_DEBUG_OBJECT (parse, "no header yet, cannot convert");
    res = FALSE;
    goto done;
  }
}
