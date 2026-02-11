gst_rtp_channels_create_default (gint channels)
{
  gint i;
  GstAudioChannelPosition *posn;

  g_return_val_if_fail (channels > 0, NULL);

  posn = g_new (GstAudioChannelPosition, channels);

  for (i = 0; i < channels; i++)
    posn[i] = GST_AUDIO_CHANNEL_POSITION_NONE;

  return posn;
}
