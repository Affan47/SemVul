stream_set_ts_offset (GstRtpBin * bin, GstRtpBinStream * stream,
    gint64 ts_offset)
{
  gint64 prev_ts_offset;

  g_object_get (stream->buffer, "ts-offset", &prev_ts_offset, NULL);


  if (prev_ts_offset != ts_offset) {
    gint64 diff;

    diff = prev_ts_offset - ts_offset;

    GST_DEBUG_OBJECT (bin,
        "ts-offset %" G_GINT64_FORMAT ", prev %" G_GINT64_FORMAT
        ", diff: %" G_GINT64_FORMAT, ts_offset, prev_ts_offset, diff);


    if (ABS (diff) > 4 * GST_MSECOND) {
      if (ABS (diff) < (3 * GST_SECOND)) {
        g_object_set (stream->buffer, "ts-offset", ts_offset, NULL);
      } else {
        GST_WARNING_OBJECT (bin, "offset unusually large, ignoring");
      }
    } else {
      GST_DEBUG_OBJECT (bin, "offset too small, ignoring");
    }
  }
  GST_DEBUG_OBJECT (bin, "stream SSRC %08x, delta %" G_GINT64_FORMAT,
      stream->ssrc, ts_offset);
}
