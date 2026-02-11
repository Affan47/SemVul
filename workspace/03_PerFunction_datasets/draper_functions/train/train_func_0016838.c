gst_video_decoder_add_to_frame (GstVideoDecoder * decoder, int n_bytes)
{
  GstVideoDecoderPrivate *priv = decoder->priv;
  GstBuffer *buf;

  GST_LOG_OBJECT (decoder, "add %d bytes to frame", n_bytes);

  if (n_bytes == 0)
    return;

  GST_VIDEO_DECODER_STREAM_LOCK (decoder);
  if (gst_adapter_available (priv->output_adapter) == 0) {
    priv->frame_offset =
        priv->input_offset - gst_adapter_available (priv->input_adapter);
  }
  buf = gst_adapter_take_buffer (priv->input_adapter, n_bytes);

  gst_adapter_push (priv->output_adapter, buf);
  GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);
}
