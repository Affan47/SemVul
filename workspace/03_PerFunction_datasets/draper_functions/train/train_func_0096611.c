gst_audio_invert_setup (GstAudioFilter * base, const GstAudioInfo * info)
{
  GstAudioInvert *filter = GST_AUDIO_INVERT (base);
  gboolean ret = TRUE;

  switch (GST_AUDIO_INFO_FORMAT (info)) {
    case GST_AUDIO_FORMAT_S16:
      filter->process = (GstAudioInvertProcessFunc)
          gst_audio_invert_transform_int;
      break;
    case GST_AUDIO_FORMAT_F32:
      filter->process = (GstAudioInvertProcessFunc)
          gst_audio_invert_transform_float;
      break;
    default:
      ret = FALSE;
      break;
  }
  return ret;
}
