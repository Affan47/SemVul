check_queue_event (GstPad * pad, GstEvent * event, gpointer user_data)
{
  GstElement *queue = GST_ELEMENT_CAST (user_data);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:
      GST_DEBUG ("EOS event, mark EOS");
      g_object_set_data (G_OBJECT (queue), "eos", GINT_TO_POINTER (1));
      break;
    case GST_EVENT_FLUSH_STOP:
      GST_DEBUG ("FLUSH_STOP event, remove EOS");
      g_object_set_data (G_OBJECT (queue), "eos", NULL);
      break;
    default:
      GST_DEBUG ("uninteresting event %s", GST_EVENT_TYPE_NAME (event));
      break;
  }
  return TRUE;
}
