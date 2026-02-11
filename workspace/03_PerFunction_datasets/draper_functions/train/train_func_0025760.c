gst_fake_sink_event (GstBaseSink * bsink, GstEvent * event)
{
  GstFakeSink *sink = GST_FAKE_SINK (bsink);

  if (!sink->silent) {
    const GstStructure *s;
    gchar *sstr;

    GST_OBJECT_LOCK (sink);
    g_free (sink->last_message);

    if (GST_EVENT_TYPE (event) == GST_EVENT_SINK_MESSAGE) {
      GstMessage *msg;

      gst_event_parse_sink_message (event, &msg);
      sstr = gst_structure_to_string (msg->structure);
      sink->last_message =
          g_strdup_printf ("message ******* (%s:%s) M (type: %d, %s) %p",
          GST_DEBUG_PAD_NAME (GST_BASE_SINK_CAST (sink)->sinkpad),
          GST_MESSAGE_TYPE (msg), sstr, msg);
      gst_message_unref (msg);
    } else {
      if ((s = gst_event_get_structure (event))) {
        sstr = gst_structure_to_string (s);
      } else {
        sstr = g_strdup ("");
      }

      sink->last_message =
          g_strdup_printf ("event   ******* (%s:%s) E (type: %d, %s) %p",
          GST_DEBUG_PAD_NAME (GST_BASE_SINK_CAST (sink)->sinkpad),
          GST_EVENT_TYPE (event), sstr, event);
    }
    g_free (sstr);
    GST_OBJECT_UNLOCK (sink);

    gst_fake_sink_notify_last_message (sink);
  }

  if (GST_BASE_SINK_CLASS (parent_class)->event) {
    return GST_BASE_SINK_CLASS (parent_class)->event (bsink, event);
  } else {
    return TRUE;
  }
}
