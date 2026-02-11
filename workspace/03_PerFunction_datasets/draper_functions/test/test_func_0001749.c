gst_capsfilter_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  GstCapsFilter *filter = GST_CAPSFILTER (trans);

  if (GST_EVENT_TYPE (event) == GST_EVENT_FLUSH_STOP) {
    GList *l;

    for (l = filter->pending_events; l; l = l->next) {
      if (GST_EVENT_TYPE (l->data) == GST_EVENT_SEGMENT) {
        gst_event_unref (l->data);
        filter->pending_events = g_list_delete_link (filter->pending_events, l);
        break;
      }
    }
  }

  if (!GST_EVENT_IS_STICKY (event)
      || GST_EVENT_TYPE (event) <= GST_EVENT_CAPS)
    goto done;


  if (GST_EVENT_TYPE (event) == GST_EVENT_EOS) {
    GList *l;

    for (l = g_list_last (filter->pending_events); l; l = l->prev) {
      GST_LOG_OBJECT (trans, "Forwarding %s event",
          GST_EVENT_TYPE_NAME (l->data));
      GST_BASE_TRANSFORM_CLASS (parent_class)->sink_event (trans, l->data);
    }
    g_list_free (filter->pending_events);
    filter->pending_events = NULL;
  } else if (!gst_pad_has_current_caps (trans->sinkpad)) {
    GST_LOG_OBJECT (trans, "Got %s event before caps, queueing",
        GST_EVENT_TYPE_NAME (event));

    filter->pending_events = g_list_prepend (filter->pending_events, event);

    return TRUE;
  }

done:

  GST_LOG_OBJECT (trans, "Forwarding %s event", GST_EVENT_TYPE_NAME (event));
  return GST_BASE_TRANSFORM_CLASS (parent_class)->sink_event (trans, event);
}
