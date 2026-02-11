gst_audio_resample_set_caps (GstBaseTransform * base, GstCaps * incaps,
    GstCaps * outcaps)
{
  gboolean ret;
  gint width, inrate, outrate, channels;
  gboolean fp;
  GstAudioResample *resample = GST_AUDIO_RESAMPLE (base);
  GstAudioInfo in, out;

  GST_LOG ("incaps %" GST_PTR_FORMAT ", outcaps %"
      GST_PTR_FORMAT, incaps, outcaps);

  if (!gst_audio_info_from_caps (&in, incaps))
    goto invalid_incaps;
  if (!gst_audio_info_from_caps (&out, outcaps))
    goto invalid_outcaps;


  width = GST_AUDIO_FORMAT_INFO_WIDTH (in.finfo);
  channels = GST_AUDIO_INFO_CHANNELS (&in);
  inrate = GST_AUDIO_INFO_RATE (&in);
  outrate = GST_AUDIO_INFO_RATE (&out);
  fp = GST_AUDIO_FORMAT_INFO_IS_FLOAT (in.finfo);

  ret =
      gst_audio_resample_update_state (resample, width, channels, inrate,
      outrate, resample->quality, fp, resample->sinc_filter_mode,
      resample->sinc_filter_auto_threshold);

  if (G_UNLIKELY (!ret))
    return FALSE;

  return TRUE;


invalid_incaps:
  {
    GST_ERROR_OBJECT (base, "invalid incaps");
    return FALSE;
  }
invalid_outcaps:
  {
    GST_ERROR_OBJECT (base, "invalid outcaps");
    return FALSE;
  }
}
