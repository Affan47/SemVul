gst_message_parse_state_changed (GstMessage * message,
    GstState * oldstate, GstState * newstate, GstState * pending)
{
  g_return_if_fail (GST_IS_MESSAGE (message));
  g_return_if_fail (GST_MESSAGE_TYPE (message) == GST_MESSAGE_STATE_CHANGED);

  if (oldstate)
    *oldstate = (GstState)
        g_value_get_enum (gst_structure_id_get_value (message->structure,
            GST_QUARK (OLD_STATE)));
  if (newstate)
    *newstate = (GstState)
        g_value_get_enum (gst_structure_id_get_value (message->structure,
            GST_QUARK (NEW_STATE)));
  if (pending)
    *pending = (GstState)
        g_value_get_enum (gst_structure_id_get_value (message->structure,
            GST_QUARK (PENDING_STATE)));
}
