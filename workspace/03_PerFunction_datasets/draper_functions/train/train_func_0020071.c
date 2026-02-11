gst_oss4_sink_init (GstOss4Sink * osssink)
{
  const gchar *device;

  device = g_getenv ("AUDIODEV");
  if (device == NULL)
    device = DEFAULT_DEVICE;
  osssink->device = g_strdup (device);
  osssink->fd = -1;
  osssink->bytes_per_sample = 0;
  osssink->probed_caps = NULL;
  osssink->device_name = NULL;
  osssink->mute_volume = 100 | (100 << 8);
}
