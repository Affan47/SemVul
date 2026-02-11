gst_audio_decoder_set_latency (GstAudioDecoder * dec,
    GstClockTime min, GstClockTime max)
{
  g_return_if_fail (GST_IS_AUDIO_DECODER (dec));

  GST_OBJECT_LOCK (dec);
  dec->priv->ctx.min_latency = min;
  dec->priv->ctx.max_latency = max;
  GST_OBJECT_UNLOCK (dec);
}
