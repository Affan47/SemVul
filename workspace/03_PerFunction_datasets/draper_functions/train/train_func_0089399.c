gst_clock_set_calibration (GstClock * clock, GstClockTime internal, GstClockTime
    external, GstClockTime rate_num, GstClockTime rate_denom)
{
  g_return_if_fail (GST_IS_CLOCK (clock));
  g_return_if_fail (rate_num != GST_CLOCK_TIME_NONE);
  g_return_if_fail (rate_denom > 0 && rate_denom != GST_CLOCK_TIME_NONE);

  write_seqlock (clock);
  GST_CAT_DEBUG_OBJECT (GST_CAT_CLOCK, clock,
      "internal %" GST_TIME_FORMAT " external %" GST_TIME_FORMAT " %"
      G_GUINT64_FORMAT "/%" G_GUINT64_FORMAT " = %f", GST_TIME_ARGS (internal),
      GST_TIME_ARGS (external), rate_num, rate_denom,
      gst_guint64_to_gdouble (rate_num) / gst_guint64_to_gdouble (rate_denom));

  clock->internal_calibration = internal;
  clock->external_calibration = external;
  clock->rate_numerator = rate_num;
  clock->rate_denominator = rate_denom;
  write_sequnlock (clock);
}
