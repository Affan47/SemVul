gst_base_transform_src_eventfunc (GstBaseTransform * trans, GstEvent * event)
{
  gboolean ret;

  GST_DEBUG_OBJECT (trans, "handling event %p %" GST_PTR_FORMAT, event, event);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
      break;
    case GST_EVENT_NAVIGATION:
      break;
    case GST_EVENT_QOS:
    {
      gdouble proportion;
      GstClockTimeDiff diff;
      GstClockTime timestamp;

      gst_event_parse_qos (event, &proportion, &diff, &timestamp);
      gst_base_transform_update_qos (trans, proportion, diff, timestamp);
      break;
    }
    default:
      break;
  }

  ret = gst_pad_push_event (trans->sinkpad, event);

  return ret;
}
