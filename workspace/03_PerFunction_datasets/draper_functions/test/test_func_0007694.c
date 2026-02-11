gst_audio_amplify_set_process_function (GstAudioAmplify * filter, gint
    clipping_method, gint format, gint width)
{
  GstAudioAmplifyProcessFunc process;


  process = gst_audio_amplify_process_function (clipping_method, format, width);
  if (!process) {
    GST_DEBUG ("wrong format");
    return FALSE;
  }

  filter->process = process;
  filter->clipping_method = clipping_method;
  filter->format = format;
  filter->width = width;

  return TRUE;
}
