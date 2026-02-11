gst_video_decoder_get_timestamp_at_offset (GstVideoDecoder *
    decoder, guint64 offset, GstClockTime * pts, GstClockTime * dts,
    GstClockTime * duration)
{
#ifndef GST_DISABLE_GST_DEBUG
  guint64 got_offset = 0;
#endif
  Timestamp *ts;
  GList *g;

  *pts = GST_CLOCK_TIME_NONE;
  *dts = GST_CLOCK_TIME_NONE;
  *duration = GST_CLOCK_TIME_NONE;

  g = decoder->priv->timestamps;
  while (g) {
    ts = g->data;
    if (ts->offset <= offset) {
#ifndef GST_DISABLE_GST_DEBUG
      got_offset = ts->offset;
#endif
      *pts = ts->pts;
      *dts = ts->dts;
      *duration = ts->duration;
      timestamp_free (ts);
      g = g->next;
      decoder->priv->timestamps = g_list_remove (decoder->priv->timestamps, ts);
    } else {
      break;
    }
  }

  GST_LOG_OBJECT (decoder,
      "got PTS %" GST_TIME_FORMAT " DTS %" GST_TIME_FORMAT " @ offs %"
      G_GUINT64_FORMAT " (wanted offset:%" G_GUINT64_FORMAT ")",
      GST_TIME_ARGS (*pts), GST_TIME_ARGS (*dts), got_offset, offset);
}
