gst_measure_collector_event (GstBaseTransform * base, GstEvent * event)
{
  GstMeasureCollector *mc = GST_MEASURE_COLLECTOR (base);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CUSTOM_DOWNSTREAM:
      if (gst_event_has_name (event, GST_EVENT_VIDEO_MEASURE))
        gst_measure_collector_collect (mc, event);
      break;
    case GST_EVENT_EOS:
      gst_measure_collector_post_message (mc);
      gst_measure_collector_save_csv (mc);
      break;
    default:
      break;
  }

  return parent_class->event (base, event);
}
