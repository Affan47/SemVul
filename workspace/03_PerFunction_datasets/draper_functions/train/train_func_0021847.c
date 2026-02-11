forward_sticky_events (GstPad * sinkpad, GstEvent ** event, gpointer user_data)
{
  RsnInputSelector *sel = GST_INPUT_SELECTOR (user_data);

  if (GST_EVENT_TYPE (*event) == GST_EVENT_SEGMENT) {
    GstSegment *seg = &GST_SELECTOR_PAD (sinkpad)->segment;
    GstEvent *e;

    e = gst_event_new_segment (seg);
    gst_event_set_seqnum (e, GST_SELECTOR_PAD_CAST (sinkpad)->segment_seqnum);

    gst_pad_push_event (sel->srcpad, e);
  } else if (GST_EVENT_TYPE (*event) != GST_EVENT_STREAM_START) {
    GST_WARNING ("Pushing event %" GST_PTR_FORMAT, *event);
    gst_pad_push_event (sel->srcpad, gst_event_ref (*event));
  }

  return TRUE;
}
