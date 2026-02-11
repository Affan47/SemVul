gst_event_new_gap (GstClockTime timestamp, GstClockTime duration)
{
  GstEvent *event;

  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (timestamp), NULL);

  GST_CAT_TRACE (GST_CAT_EVENT, "creating gap %" GST_TIME_FORMAT " - "
      "%" GST_TIME_FORMAT " (duration: %" GST_TIME_FORMAT ")",
      GST_TIME_ARGS (timestamp), GST_TIME_ARGS (timestamp + duration),
      GST_TIME_ARGS (duration));

  event = gst_event_new_custom (GST_EVENT_GAP,
      gst_structure_new_id (GST_QUARK (EVENT_GAP),
          GST_QUARK (TIMESTAMP), GST_TYPE_CLOCK_TIME, timestamp,
          GST_QUARK (DURATION), GST_TYPE_CLOCK_TIME, duration, NULL));

  return event;
}
