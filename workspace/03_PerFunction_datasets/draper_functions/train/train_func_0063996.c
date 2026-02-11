gst_value_compare_date_time (const GValue * value1, const GValue * value2)
{
  const GstDateTime *date1 = (const GstDateTime *) g_value_get_boxed (value1);
  const GstDateTime *date2 = (const GstDateTime *) g_value_get_boxed (value2);

  if (date1 == date2)
    return GST_VALUE_EQUAL;

  if ((date1 == NULL) && (date2 != NULL)) {
    return GST_VALUE_LESS_THAN;
  }
  if ((date2 == NULL) && (date1 != NULL)) {
    return GST_VALUE_LESS_THAN;
  }


  return __gst_date_time_compare (date1, date2);
}
