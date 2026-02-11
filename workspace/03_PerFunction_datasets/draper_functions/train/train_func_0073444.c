gst_decode_pad_query (GstPad * pad, GstObject * parent, GstQuery * query)
{
  GstDecodePad *dpad = GST_DECODE_PAD (parent);
  gboolean ret = FALSE;

  CHAIN_MUTEX_LOCK (dpad->chain);
  if (!dpad->exposed && !dpad->dbin->shutdown && !dpad->chain->deadend
      && dpad->chain->elements) {
    GstDecodeElement *delem = dpad->chain->elements->data;

    ret = FALSE;
    GST_DEBUG_OBJECT (dpad->dbin,
        "calling autoplug-query for %s (element %s): %" GST_PTR_FORMAT,
        GST_PAD_NAME (dpad), GST_ELEMENT_NAME (delem->element), query);
    g_signal_emit (G_OBJECT (dpad->dbin),
        gst_decode_bin_signals[SIGNAL_AUTOPLUG_QUERY], 0, dpad, delem->element,
        query, &ret);

    if (ret)
      GST_DEBUG_OBJECT (dpad->dbin,
          "autoplug-query returned %d: %" GST_PTR_FORMAT, ret, query);
    else
      GST_DEBUG_OBJECT (dpad->dbin, "autoplug-query returned %d", ret);
  }
  CHAIN_MUTEX_UNLOCK (dpad->chain);


  if (!ret)
    ret = gst_pad_query_default (pad, parent, query);

  return ret;
}
