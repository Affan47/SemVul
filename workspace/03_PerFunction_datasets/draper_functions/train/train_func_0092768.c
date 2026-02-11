gst_video_decoder_setcaps (GstVideoDecoder * decoder, GstCaps * caps)
{
  GstVideoDecoderClass *decoder_class;
  GstVideoCodecState *state;
  gboolean ret = TRUE;

  decoder_class = GST_VIDEO_DECODER_GET_CLASS (decoder);

  GST_DEBUG_OBJECT (decoder, "setcaps %" GST_PTR_FORMAT, caps);

  GST_VIDEO_DECODER_STREAM_LOCK (decoder);

  if (decoder->priv->input_state) {
    GST_DEBUG_OBJECT (decoder,
        "Checking if caps changed old %" GST_PTR_FORMAT " new %" GST_PTR_FORMAT,
        decoder->priv->input_state->caps, caps);
    if (gst_caps_is_equal (decoder->priv->input_state->caps, caps))
      goto caps_not_changed;
  }

  state = _new_input_state (caps);

  if (G_UNLIKELY (state == NULL))
    goto parse_fail;

  if (decoder_class->set_format)
    ret = decoder_class->set_format (decoder, state);

  if (!ret)
    goto refused_format;

  if (decoder->priv->input_state)
    gst_video_codec_state_unref (decoder->priv->input_state);
  decoder->priv->input_state = state;

  GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);

  return ret;

caps_not_changed:
  {
    GST_DEBUG_OBJECT (decoder, "Caps did not change - ignore");
    GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);
    return TRUE;
  }


parse_fail:
  {
    GST_WARNING_OBJECT (decoder, "Failed to parse caps");
    GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);
    return FALSE;
  }

refused_format:
  {
    GST_VIDEO_DECODER_STREAM_UNLOCK (decoder);
    GST_WARNING_OBJECT (decoder, "Subclass refused caps");
    gst_video_codec_state_unref (state);
    return FALSE;
  }
}
