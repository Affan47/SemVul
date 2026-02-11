gst_message_parse_clock_provide (GstMessage * message, GstClock ** clock,
    gboolean * ready)
{
  const GValue *clock_gvalue;
  GstStructure *structure;

  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_CLOCK_PROVIDE);

  structure = GST_MESSAGE_STRUCTURE (message);
  clock_gvalue = gst_structure_id_get_value (structure, GST_QUARK (CLOCK));
  g_return_if_fail (clock_gvalue != NULL);
  g_return_if_fail (G_VALUE_TYPE (clock_gvalue) == GST_TYPE_CLOCK);

  if (ready)
    *ready =
        g_value_get_boolean (gst_structure_id_get_value (structure,
            GST_QUARK (READY)));
  if (clock)
    *clock = (GstClock *) g_value_get_object (clock_gvalue);
}
