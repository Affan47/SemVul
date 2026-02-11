remove_decoders (GstURIDecodeBin * bin, gboolean force)
{
  GSList *walk;

  for (walk = bin->decodebins; walk; walk = g_slist_next (walk)) {
    GstElement *decoder = GST_ELEMENT_CAST (walk->data);

    GST_DEBUG_OBJECT (bin, "removing old decoder element");
    if (force) {
      gst_element_set_state (decoder, GST_STATE_NULL);
      gst_bin_remove (GST_BIN_CAST (bin), decoder);
    } else {
      GstCaps *caps;

      gst_element_set_state (decoder, GST_STATE_READY);

      g_object_ref (decoder);
      gst_bin_remove (GST_BIN_CAST (bin), decoder);

      g_object_set (decoder, "sink-caps", NULL, NULL);
      caps = DEFAULT_CAPS;
      g_object_set (decoder, "caps", caps, NULL);
      gst_caps_unref (caps);

      g_object_force_floating (G_OBJECT (decoder));

      bin->pending_decodebins =
          g_slist_prepend (bin->pending_decodebins, decoder);
    }
  }
  g_slist_free (bin->decodebins);
  bin->decodebins = NULL;
  if (force) {
    GSList *tmp;

    for (tmp = bin->pending_decodebins; tmp; tmp = tmp->next) {
      gst_element_set_state ((GstElement *) tmp->data, GST_STATE_NULL);
      gst_object_unref ((GstElement *) tmp->data);
    }
    g_slist_free (bin->pending_decodebins);
    bin->pending_decodebins = NULL;

  }


  GST_OBJECT_FLAG_SET (bin, GST_ELEMENT_FLAG_SOURCE);
}
