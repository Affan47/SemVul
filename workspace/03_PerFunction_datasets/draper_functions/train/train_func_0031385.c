gst_decklink_sink_audiosink_event (GstPad * pad, GstObject * parent,
    GstEvent * event)
{
  gboolean res;
  GstDecklinkSink *decklinksink;

  decklinksink = GST_DECKLINK_SINK (parent);

  GST_DEBUG_OBJECT (pad, "event: %" GST_PTR_FORMAT, event);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:

      decklinksink->audio_eos = TRUE;
      decklinksink->audio_seqnum = gst_event_get_seqnum (event);
      res = gst_pad_event_default (pad, parent, event);
      break;
    default:
      res = gst_pad_event_default (pad, parent, event);
      break;
  }

  return res;
}
