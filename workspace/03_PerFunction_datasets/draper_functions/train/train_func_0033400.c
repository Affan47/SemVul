setup_element (const gchar * factory, ElementSetup setup,
    GstStaticPadTemplate * sink_template,
    GstCaps * sink_caps, GstStaticPadTemplate * src_template,
    GstCaps * src_caps)
{
  GstElement *element;
  GstBus *bus;

  if (setup) {
    element = setup (factory);
  } else {
    element = gst_check_setup_element (factory);
  }
  srcpad = gst_check_setup_src_pad (element, src_template, src_caps);
  sinkpad = gst_check_setup_sink_pad (element, sink_template, sink_caps);
  gst_pad_set_active (srcpad, TRUE);
  gst_pad_set_active (sinkpad, TRUE);

  bus = gst_bus_new ();
  gst_element_set_bus (element, bus);

  fail_unless (gst_element_set_state (element,
          GST_STATE_PLAYING) != GST_STATE_CHANGE_FAILURE,
      "could not set to playing");

  buffers = NULL;
  return element;
}
