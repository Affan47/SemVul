gst_video_encoder_setcaps (GstVideoEncoder * encoder, GstCaps * caps)
{
  GstVideoEncoderClass *encoder_class;
  GstVideoCodecState *state;
  gboolean ret;

  encoder_class = GST_VIDEO_ENCODER_GET_CLASS (encoder);


  g_return_val_if_fail (encoder_class->set_format != NULL, FALSE);

  GST_DEBUG_OBJECT (encoder, "setcaps %" GST_PTR_FORMAT, caps);

  GST_VIDEO_ENCODER_STREAM_LOCK (encoder);

  if (encoder->priv->input_state) {
    GST_DEBUG_OBJECT (encoder,
        "Checking if caps changed old %" GST_PTR_FORMAT " new %" GST_PTR_FORMAT,
        encoder->priv->input_state->caps, caps);
    if (gst_caps_is_equal (encoder->priv->input_state->caps, caps))
      goto caps_not_changed;
  }

  state = _new_input_state (caps);
  if (G_UNLIKELY (!state))
    goto parse_fail;

  if (encoder->priv->input_state
      && gst_video_info_is_equal (&state->info,
          &encoder->priv->input_state->info)) {
    gst_video_codec_state_unref (state);
    goto caps_not_changed;
  }

  if (encoder_class->reset) {
    GST_FIXME_OBJECT (encoder, "GstVideoEncoder::reset() is deprecated");
    ret = encoder_class->reset (encoder, TRUE);
  }


  ret = encoder_class->set_format (encoder, state);
  if (ret) {
    if (encoder->priv->input_state)
      gst_video_codec_state_unref (encoder->priv->input_state);
    encoder->priv->input_state = state;
  } else {
    gst_video_codec_state_unref (state);
  }

  GST_VIDEO_ENCODER_STREAM_UNLOCK (encoder);

  if (!ret)
    GST_WARNING_OBJECT (encoder, "rejected caps %" GST_PTR_FORMAT, caps);

  return ret;

caps_not_changed:
  {
    GST_DEBUG_OBJECT (encoder, "Caps did not change - ignore");
    GST_VIDEO_ENCODER_STREAM_UNLOCK (encoder);
    return TRUE;
  }


parse_fail:
  {
    GST_WARNING_OBJECT (encoder, "Failed to parse caps");
    GST_VIDEO_ENCODER_STREAM_UNLOCK (encoder);
    return FALSE;
  }
}
