gst_funnel_src_event (GstPad * pad, GstEvent * event)
{
  GstElement *funnel;
  GstIterator *iter;
  GstPad *sinkpad;
  gboolean result = FALSE;
  gboolean done = FALSE;

  funnel = gst_pad_get_parent_element (pad);
  if (G_UNLIKELY (funnel == NULL)) {
    gst_event_unref (event);
    return FALSE;
  }

  iter = gst_element_iterate_sink_pads (funnel);

  while (!done) {
    switch (gst_iterator_next (iter, (gpointer) & sinkpad)) {
      case GST_ITERATOR_OK:
        gst_event_ref (event);
        result |= gst_pad_push_event (sinkpad, event);
        gst_object_unref (sinkpad);
        break;
      case GST_ITERATOR_RESYNC:
        gst_iterator_resync (iter);
        result = FALSE;
        break;
      case GST_ITERATOR_ERROR:
        GST_WARNING_OBJECT (funnel, "Error iterating sinkpads");
      case GST_ITERATOR_DONE:
        done = TRUE;
        break;
    }
  }
  gst_iterator_free (iter);
  gst_object_unref (funnel);
  gst_event_unref (event);

  return result;
}
