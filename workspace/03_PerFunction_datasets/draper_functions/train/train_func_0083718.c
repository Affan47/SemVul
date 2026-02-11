gst_ogm_parse_sink_event (GstPad * pad, GstEvent * event)
{
  GstOgmParse *ogm = GST_OGM_PARSE (gst_pad_get_parent (pad));
  gboolean res;

  GST_LOG_OBJECT (ogm, "processing %s event", GST_EVENT_TYPE_NAME (event));

  GST_OBJECT_LOCK (ogm);
  if (ogm->srcpad == NULL) {
    ogm->cached_events = g_list_append (ogm->cached_events, event);
    GST_OBJECT_UNLOCK (ogm);
    res = TRUE;
  } else {
    GST_OBJECT_UNLOCK (ogm);
    res = gst_pad_event_default (pad, event);
  }

  gst_object_unref (ogm);
  return res;
}
