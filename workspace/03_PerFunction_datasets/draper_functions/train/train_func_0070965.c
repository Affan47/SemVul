gst_live_adder_src_event (GstPad * pad, GstEvent * event)
{
  GstLiveAdder *adder;
  gboolean result;

  adder = GST_LIVE_ADDER (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_QOS:

      result = FALSE;
      break;
    case GST_EVENT_NAVIGATION:

      result = FALSE;
      break;
    default:

      result = forward_event (adder, event);
      break;
  }

  gst_event_unref (event);
  gst_object_unref (adder);

  return result;
}
