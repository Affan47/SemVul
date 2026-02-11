gst_oss4_source_close (GstAudioSrc * asrc)
{
  GstOss4Source *oss;

  oss = GST_OSS4_SOURCE (asrc);

  if (oss->fd != -1) {
    GST_DEBUG_OBJECT (oss, "closing device");
    close (oss->fd);
    oss->fd = -1;
  }

  oss->bytes_per_sample = 0;

  gst_caps_replace (&oss->probed_caps, NULL);

  g_free (oss->open_device);
  oss->open_device = NULL;

  g_free (oss->device_name);
  oss->device_name = NULL;

  gst_oss4_source_free_mixer_tracks (oss);

  return TRUE;
}
