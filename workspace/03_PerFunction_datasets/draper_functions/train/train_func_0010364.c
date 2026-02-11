get_compatible_unlinked_pad (GstElement * element, GstPad * pad)
{
  GstPad *res = NULL;
  GstIterator *pads;
  gboolean done = FALSE;
  GstCaps *srccaps;

  GST_DEBUG ("element : %s, pad %s:%s",
      GST_ELEMENT_NAME (element), GST_DEBUG_PAD_NAME (pad));

  if (GST_PAD_DIRECTION (pad) == GST_PAD_SRC)
    pads = gst_element_iterate_sink_pads (element);
  else
    pads = gst_element_iterate_src_pads (element);
  srccaps = gst_pad_get_caps_reffed (pad);

  GST_DEBUG ("srccaps %" GST_PTR_FORMAT, srccaps);

  while (!done) {
    gpointer padptr;

    switch (gst_iterator_next (pads, &padptr)) {
      case GST_ITERATOR_OK:
      {
        GstPad *testpad = (GstPad *) padptr;

        if (gst_pad_is_linked (testpad)) {
          gst_object_unref (testpad);
        } else {
          GstCaps *sinkcaps = gst_pad_get_caps_reffed (testpad);

          GST_DEBUG ("sinkccaps %" GST_PTR_FORMAT, sinkcaps);

          if (gst_caps_can_intersect (srccaps, sinkcaps)) {
            res = testpad;
            done = TRUE;
          } else
            gst_object_unref (testpad);
          gst_caps_unref (sinkcaps);
        }
      }
        break;
      case GST_ITERATOR_DONE:
      case GST_ITERATOR_ERROR:
        done = TRUE;
        break;
      case GST_ITERATOR_RESYNC:
        gst_iterator_resync (pads);
        break;
    }
  }
  gst_iterator_free (pads);
  gst_caps_unref (srccaps);

  return res;
}
