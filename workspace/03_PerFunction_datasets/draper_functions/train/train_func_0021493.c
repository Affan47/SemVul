sink_accepts_caps (GstElement * sink, GstCaps * caps)
{
  GstPad *sinkpad;


  if (GST_STATE (sink) < GST_STATE_READY &&
      gst_element_set_state (sink,
          GST_STATE_READY) == GST_STATE_CHANGE_FAILURE) {
    return FALSE;
  }

  if ((sinkpad = gst_element_get_static_pad (sink, "sink"))) {


    if (!gst_pad_accept_caps (sinkpad, caps)) {
      gst_object_unref (sinkpad);
      return FALSE;
    }
    gst_object_unref (sinkpad);
  }

  return TRUE;
}
