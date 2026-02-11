gst_audio_convert_get_unit_size (GstBaseTransform * base, GstCaps * caps,
    gsize * size)
{
  GstAudioInfo info;

  g_assert (size);

  if (!gst_audio_info_from_caps (&info, caps))
    goto parse_error;

  *size = info.bpf;
  GST_INFO_OBJECT (base, "unit_size = %" G_GSIZE_FORMAT, *size);

  return TRUE;

parse_error:
  {
    GST_INFO_OBJECT (base, "failed to parse caps to get unit_size");
    return FALSE;
  }
}
