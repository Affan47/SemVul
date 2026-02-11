gst_speed_convert (GstSpeed * filter, GstFormat src_format, gint64 src_value,
    GstFormat * dest_format, gint64 * dest_value)
{
  gboolean ret = TRUE;
  guint scale = 1;

  if (src_format == *dest_format) {
    *dest_value = src_value;
    return TRUE;
  }

  switch (src_format) {
    case GST_FORMAT_BYTES:
      switch (*dest_format) {
        case GST_FORMAT_DEFAULT:
          if (GST_AUDIO_INFO_BPF (&filter->info) == 0) {
            ret = FALSE;
            break;
          }
          *dest_value = src_value / GST_AUDIO_INFO_BPF (&filter->info);
          break;
        case GST_FORMAT_TIME:
        {
          gint byterate =
              GST_AUDIO_INFO_BPF (&filter->info) *
              GST_AUDIO_INFO_RATE (&filter->info);

          if (byterate == 0) {
            ret = FALSE;
            break;
          }
          *dest_value = src_value * GST_SECOND / byterate;
          break;
        }
        default:
          ret = FALSE;
      }
      break;
    case GST_FORMAT_DEFAULT:
      switch (*dest_format) {
        case GST_FORMAT_BYTES:
          *dest_value = src_value * GST_AUDIO_INFO_BPF (&filter->info);
          break;
        case GST_FORMAT_TIME:
          if (GST_AUDIO_INFO_RATE (&filter->info) == 0) {
            ret = FALSE;
            break;
          }
          *dest_value =
              src_value * GST_SECOND / GST_AUDIO_INFO_RATE (&filter->info);
          break;
        default:
          ret = FALSE;
      }
      break;
    case GST_FORMAT_TIME:
      switch (*dest_format) {
        case GST_FORMAT_BYTES:
          scale = GST_AUDIO_INFO_BPF (&filter->info);

        case GST_FORMAT_DEFAULT:
          *dest_value =
              src_value * scale * GST_AUDIO_INFO_RATE (&filter->info) /
              GST_SECOND;
          break;
        default:
          ret = FALSE;
      }
      break;
    default:
      ret = FALSE;
  }

  return ret;

}
