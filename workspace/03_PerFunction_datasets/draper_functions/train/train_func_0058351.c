gst_video_decoder_add_timestamp (GstVideoDecoder * decoder, GstBuffer * buffer)
{
  GstVideoDecoderPrivate *priv = decoder->priv;
  Timestamp *ts;

  ts = g_slice_new (Timestamp);

  GST_LOG_OBJECT (decoder,
      "adding PTS %" GST_TIME_FORMAT " DTS %" GST_TIME_FORMAT
      " (offset:%" G_GUINT64_FORMAT ")",
      GST_TIME_ARGS (GST_BUFFER_PTS (buffer)),
      GST_TIME_ARGS (GST_BUFFER_DTS (buffer)), priv->input_offset);

  ts->offset = priv->input_offset;
  ts->pts = GST_BUFFER_PTS (buffer);
  ts->dts = GST_BUFFER_DTS (buffer);
  ts->duration = GST_BUFFER_DURATION (buffer);

  priv->timestamps = g_list_append (priv->timestamps, ts);
}
