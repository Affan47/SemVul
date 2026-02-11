gst_video_decoder_get_output_state (GstVideoDecoder * decoder)
{
  GstVideoCodecState *state = NULL;

  GST_OBJECT_LOCK (decoder);
  if (decoder->priv->output_state)
    state = gst_video_codec_state_ref (decoder->priv->output_state);
  GST_OBJECT_UNLOCK (decoder);

  return state;
}
