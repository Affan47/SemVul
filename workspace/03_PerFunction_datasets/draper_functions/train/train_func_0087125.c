gst_stream_volume_convert_volume (GstStreamVolumeFormat from,
    GstStreamVolumeFormat to, gdouble val)
{
  switch (from) {
    case GST_STREAM_VOLUME_FORMAT_LINEAR:
      g_return_val_if_fail (val >= 0.0, 0.0);
      switch (to) {
        case GST_STREAM_VOLUME_FORMAT_LINEAR:
          return val;
        case GST_STREAM_VOLUME_FORMAT_CUBIC:
          return pow (val, 1 / 3.0);
        case GST_STREAM_VOLUME_FORMAT_DB:
          return 20.0 * log10 (val);
      }
      break;
    case GST_STREAM_VOLUME_FORMAT_CUBIC:
      g_return_val_if_fail (val >= 0.0, 0.0);
      switch (to) {
        case GST_STREAM_VOLUME_FORMAT_LINEAR:
          return val * val * val;
        case GST_STREAM_VOLUME_FORMAT_CUBIC:
          return val;
        case GST_STREAM_VOLUME_FORMAT_DB:
          return 3.0 * 20.0 * log10 (val);
      }
      break;
    case GST_STREAM_VOLUME_FORMAT_DB:
      switch (to) {
        case GST_STREAM_VOLUME_FORMAT_LINEAR:
          return pow (10.0, val / 20.0);
        case GST_STREAM_VOLUME_FORMAT_CUBIC:
          return pow (10.0, val / (3.0 * 20.0));
        case GST_STREAM_VOLUME_FORMAT_DB:
          return val;
      }
      break;
  }
  g_return_val_if_reached (0.0);
}
