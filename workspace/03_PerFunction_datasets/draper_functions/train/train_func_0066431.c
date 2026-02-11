gst_type_find_element_chain_do_typefinding (GstTypeFindElement * typefind)
{
  GstTypeFindProbability probability;
  GstCaps *caps;

  GST_OBJECT_LOCK (typefind);
  if (GST_BUFFER_SIZE (typefind->store) < TYPE_FIND_MIN_SIZE) {
    GST_DEBUG_OBJECT (typefind, "not enough data for typefinding yet "
        "(%u bytes)", GST_BUFFER_SIZE (typefind->store));
    GST_OBJECT_UNLOCK (typefind);
    return GST_FLOW_OK;
  }

  caps = gst_type_find_helper_for_buffer (GST_OBJECT (typefind),
      typefind->store, &probability);
  if (caps == NULL && GST_BUFFER_SIZE (typefind->store) > TYPE_FIND_MAX_SIZE) {
    GST_OBJECT_UNLOCK (typefind);
    GST_ELEMENT_ERROR (typefind, STREAM, TYPE_NOT_FOUND, (NULL), (NULL));
    stop_typefinding (typefind);
    return GST_FLOW_ERROR;
  } else if (caps == NULL) {
    GST_OBJECT_UNLOCK (typefind);
    GST_DEBUG_OBJECT (typefind, "no caps found with %u bytes of data, "
        "waiting for more data", GST_BUFFER_SIZE (typefind->store));
    return GST_FLOW_OK;
  }


  if (probability < typefind->min_probability) {
    GST_DEBUG_OBJECT (typefind, "found caps %" GST_PTR_FORMAT ", but "
        "probability is %u which is lower than the required minimum of %u",
        caps, probability, typefind->min_probability);

    gst_caps_replace (&caps, NULL);

    if (GST_BUFFER_SIZE (typefind->store) >= TYPE_FIND_MAX_SIZE) {
      GST_OBJECT_UNLOCK (typefind);
      GST_ELEMENT_ERROR (typefind, STREAM, TYPE_NOT_FOUND, (NULL), (NULL));
      stop_typefinding (typefind);
      return GST_FLOW_ERROR;
    }

    GST_OBJECT_UNLOCK (typefind);
    GST_DEBUG_OBJECT (typefind, "waiting for more data to try again");
    return GST_FLOW_OK;
  }
  GST_OBJECT_UNLOCK (typefind);


  g_signal_emit (typefind, gst_type_find_element_signals[HAVE_TYPE], 0,
      probability, caps);


  stop_typefinding (typefind);
  gst_caps_unref (caps);
  return GST_FLOW_OK;
}
