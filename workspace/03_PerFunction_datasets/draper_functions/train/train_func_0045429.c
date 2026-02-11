gst_audio_resample_get_unit_size (GstBaseTransform * base, GstCaps * caps,
    gsize * size)
{
  GstAudioInfo info;

  if (!gst_audio_info_from_caps (&info, caps))
    goto invalid_caps;

  *size = GST_AUDIO_INFO_BPF (&info);

  return TRUE;


invalid_caps:
  {
    GST_ERROR_OBJECT (base, "invalid caps");
    return FALSE;
  }
}
