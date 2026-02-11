gst_frei0r_mixer_sink_event (GstCollectPads * pads, GstCollectData * cdata,
    GstEvent * event, GstFrei0rMixer * self)
{
  gboolean ret = TRUE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CAPS:
    {
      GstCaps *caps;
      gst_event_parse_caps (event, &caps);
      ret = gst_frei0r_mixer_set_caps (self, cdata->pad, caps);
      gst_event_unref (event);
      break;
    }
    default:
      ret = gst_collect_pads_event_default (pads, cdata, event, FALSE);
      break;
  }
  return ret;
}
