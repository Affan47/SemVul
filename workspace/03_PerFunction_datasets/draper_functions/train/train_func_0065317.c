gst_icydemux_handle_event (GstPad * pad, GstEvent * event)
{
  GstICYDemux *icydemux = GST_ICYDEMUX (GST_PAD_PARENT (pad));
  gboolean result;

  if (GST_EVENT_TYPE (event) == GST_EVENT_TAG) {
    GstTagList *tags;

    gst_event_parse_tag (event, &tags);
    result = gst_icydemux_tag_found (icydemux, gst_tag_list_copy (tags));
    gst_event_unref (event);
    return result;
  }

  if (icydemux->typefinding) {
    switch (GST_EVENT_TYPE (event)) {
      case GST_EVENT_FLUSH_STOP:
        g_list_foreach (icydemux->cached_events,
            (GFunc) gst_mini_object_unref, NULL);
        g_list_free (icydemux->cached_events);
        icydemux->cached_events = NULL;

        return gst_pad_event_default (pad, event);
      default:
        icydemux->cached_events = g_list_append (icydemux->cached_events,
            event);
        return TRUE;
    }
  } else {
    return gst_pad_event_default (pad, event);
  }
}
