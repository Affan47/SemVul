gst_audio_rate_src_event (GstPad * pad, GstEvent * event)
{
  gboolean res;
  GstAudioRate *audiorate;

  audiorate = GST_AUDIO_RATE (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    default:
      res = gst_pad_push_event (audiorate->sinkpad, event);
      break;
  }

  gst_object_unref (audiorate);

  return res;
}
