gst_dtmf_src_post_message (GstDTMFSrc * dtmfsrc, const gchar * message_name,
    GstDTMFSrcEvent * event)
{
  GstStructure *s = NULL;

  switch (event->event_type) {
    case DTMF_EVENT_TYPE_START:
      s = gst_structure_new (message_name,
          "type", G_TYPE_INT, 1,
          "method", G_TYPE_INT, 2,
          "start", G_TYPE_BOOLEAN, TRUE,
          "number", G_TYPE_INT, event->event_number,
          "volume", G_TYPE_INT, event->volume, NULL);
      break;
    case DTMF_EVENT_TYPE_STOP:
      s = gst_structure_new (message_name,
          "type", G_TYPE_INT, 1, "method", G_TYPE_INT, 2,
          "start", G_TYPE_BOOLEAN, FALSE, NULL);
      break;
    case DTMF_EVENT_TYPE_PAUSE_TASK:
      return;
  }

  if (s)
    gst_element_post_message (GST_ELEMENT (dtmfsrc),
        gst_message_new_element (GST_OBJECT (dtmfsrc), s));
}
