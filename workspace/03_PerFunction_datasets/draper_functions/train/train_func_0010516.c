gst_clock_new_periodic_id (GstClock * clock, GstClockTime start_time,
    GstClockTime interval)
{
  g_return_val_if_fail (GST_IS_CLOCK (clock), NULL);
  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (start_time), NULL);
  g_return_val_if_fail (interval != 0, NULL);
  g_return_val_if_fail (GST_CLOCK_TIME_IS_VALID (interval), NULL);

  return gst_clock_entry_new (clock,
      start_time, interval, GST_CLOCK_ENTRY_PERIODIC);
}
