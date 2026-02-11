gst_event_parse_seek (GstEvent * event, gdouble * rate,
    GstFormat * format, GstSeekFlags * flags, GstSeekType * start_type,
    gint64 * start, GstSeekType * stop_type, gint64 * stop)
{
  const GstStructure *structure;

  g_return_if_fail (GST_IS_EVENT (event));
  g_return_if_fail (GST_EVENT_TYPE (event) == GST_EVENT_SEEK);

  structure = GST_EVENT_STRUCTURE (event);
  if (rate)
    *rate =
        g_value_get_double (gst_structure_id_get_value (structure,
            GST_QUARK (RATE)));
  if (format)
    *format = (GstFormat)
        g_value_get_enum (gst_structure_id_get_value (structure,
            GST_QUARK (FORMAT)));
  if (flags)
    *flags = (GstSeekFlags)
        g_value_get_flags (gst_structure_id_get_value (structure,
            GST_QUARK (FLAGS)));
  if (start_type)
    *start_type = (GstSeekType)
        g_value_get_enum (gst_structure_id_get_value (structure,
            GST_QUARK (CUR_TYPE)));
  if (start)
    *start =
        g_value_get_int64 (gst_structure_id_get_value (structure,
            GST_QUARK (CUR)));
  if (stop_type)
    *stop_type = (GstSeekType)
        g_value_get_enum (gst_structure_id_get_value (structure,
            GST_QUARK (STOP_TYPE)));
  if (stop)
    *stop =
        g_value_get_int64 (gst_structure_id_get_value (structure,
            GST_QUARK (STOP)));
}
