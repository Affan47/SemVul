new_decoded_pad_cb (GstElement * decodebin, GstPad * new_pad, gboolean last,
    GstElement * pipeline)
{
  GstElement *fakesink;
  GstPad *sinkpad;

  fakesink = gst_element_factory_make ("fakesink", NULL);
  gst_bin_add (GST_BIN (pipeline), fakesink);

  sinkpad = gst_element_get_static_pad (fakesink, "sink");
  if (GST_PAD_LINK_FAILED (gst_pad_link (new_pad, sinkpad))) {
    g_warning ("Failed to link %s:%s to %s:%s", GST_DEBUG_PAD_NAME (new_pad),
        GST_DEBUG_PAD_NAME (sinkpad));
    gst_bin_remove (GST_BIN (pipeline), fakesink);
  } else {
    gst_element_set_state (fakesink, GST_STATE_PAUSED);
  }
}
