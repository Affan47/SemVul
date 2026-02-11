forward_sticky_events (GstPad * pad, GstEvent ** event, gpointer user_data)
{
  GstValve *valve = user_data;

  if (!gst_pad_push_event (valve->srcpad, gst_event_ref (*event)))
    valve->need_repush_sticky = TRUE;

  return TRUE;
}
