gst_multipart_find_pad_by_mime (GstMultipartDemux * demux, gchar * mime,
    gboolean * created)
{
  GSList *walk;

  walk = demux->srcpads;
  while (walk) {
    GstMultipartPad *pad = (GstMultipartPad *) walk->data;

    if (!strcmp (pad->mime, mime)) {
      if (created) {
        *created = FALSE;
      }
      return pad;
    }

    walk = walk->next;
  }

  {
    GstPad *pad;
    GstMultipartPad *mppad;
    gchar *name;
    const gchar *capsname;
    GstCaps *caps;

    mppad = g_new0 (GstMultipartPad, 1);

    GST_DEBUG_OBJECT (demux, "creating pad with mime: %s", mime);

    name = g_strdup_printf ("src_%u", demux->numpads);
    pad =
        gst_pad_new_from_static_template (&multipart_demux_src_template_factory,
        name);
    g_free (name);

    mppad->pad = pad;
    mppad->mime = g_strdup (mime);
    mppad->last_ret = GST_FLOW_OK;
    mppad->last_ts = GST_CLOCK_TIME_NONE;
    mppad->discont = TRUE;

    demux->srcpads = g_slist_prepend (demux->srcpads, mppad);
    demux->numpads++;


    capsname = gst_multipart_demux_get_gstname (demux, mime);
    caps = gst_caps_from_string (capsname);
    GST_DEBUG_OBJECT (demux, "caps for pad: %s", capsname);
    gst_pad_use_fixed_caps (pad);
    gst_pad_set_active (pad, TRUE);
    gst_pad_set_caps (pad, caps);
    gst_caps_unref (caps);

    gst_element_add_pad (GST_ELEMENT_CAST (demux), pad);

    if (created) {
      *created = TRUE;
    }

    if (demux->singleStream) {
      gst_element_no_more_pads (GST_ELEMENT_CAST (demux));
    }

    return mppad;
  }
}
