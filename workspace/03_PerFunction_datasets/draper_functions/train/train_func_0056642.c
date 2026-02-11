gst_audio_decoder_get_min_latency (GstAudioDecoder * dec)
{
  GstClockTime result;

  g_return_val_if_fail (GST_IS_AUDIO_DECODER (dec), FALSE);

  GST_OBJECT_LOCK (dec);
  result = dec->priv->latency;
  GST_OBJECT_UNLOCK (dec);

  return result;
}
