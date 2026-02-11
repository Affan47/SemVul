gst_audio_resample_stop (GstBaseTransform * base)
{
  GstAudioResample *resample = GST_AUDIO_RESAMPLE (base);

  if (resample->state) {
    resample->funcs->destroy (resample->state);
    resample->state = NULL;
  }

  resample->funcs = NULL;

  g_free (resample->tmp_in);
  resample->tmp_in = NULL;
  resample->tmp_in_size = 0;

  g_free (resample->tmp_out);
  resample->tmp_out = NULL;
  resample->tmp_out_size = 0;

  gst_caps_replace (&resample->sinkcaps, NULL);
  gst_caps_replace (&resample->srccaps, NULL);

  return TRUE;
}
