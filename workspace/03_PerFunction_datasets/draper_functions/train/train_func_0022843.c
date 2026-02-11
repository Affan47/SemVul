gst_video_decoder_set_output_state (GstVideoDecoder * decoder,
    GstVideoFormat fmt, guint width, guint height,
    GstVideoCodecState * reference)
{
  GstVideoDecoderPrivate *priv = decoder->priv;
  GstVideoCodecState *state;

  GST_DEBUG_OBJECT (decoder, "fmt:%d, width:%d, height:%d, reference:%p",
      fmt, width, height, reference);


  state = _new_output_state (fmt, width, height, reference);

  GST_VIDEO_DECODER_STREAM_LOCK (decoder);

  GST_OBJECT_LOCK (decoder);

  if (priv->output_state)
    gst_video_codec_state_unref (priv->output_state);
  priv->output_state = gst_video_codec_state_ref (state);

  if (priv->output_state != NULL && priv->output_state->info.fps_n > 0) {
    priv->qos_frame_duration =
        gst_util_uint64_scale (GST_SECOND, priv->output_state->info.fps_d,
        priv->output_state->info.fps_n);
  } else {
    priv->qos_frame_duration = 0;
  }
  priv->output_state_changed = TRUE;
  GST_OBJECT_UNLOCK (decoder);

  GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);

  return state;
}
