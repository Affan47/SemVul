_interpolate_linear (GstClockTime timestamp1, gdouble value1,
    GstClockTime timestamp2, gdouble value2, GstClockTime timestamp)
{
  if (GST_CLOCK_TIME_IS_VALID (timestamp2)) {
    gdouble slope;

    slope =
        (value2 - value1) / gst_guint64_to_gdouble (timestamp2 - timestamp1);
    return value1 + (gst_guint64_to_gdouble (timestamp - timestamp1) * slope);
  } else {
    return value1;
  }
}
