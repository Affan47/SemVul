gst_audio_encoder_getcaps_default (GstAudioEncoder * enc, GstCaps * filter)
{
  GstCaps *caps;

  caps = gst_audio_encoder_proxy_getcaps (enc, NULL, filter);
  GST_LOG_OBJECT (enc, "returning caps %" GST_PTR_FORMAT, caps);

  return caps;
}
