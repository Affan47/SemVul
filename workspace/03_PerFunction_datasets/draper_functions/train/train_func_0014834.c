sink_accepts_caps (GstPlayBin * playbin, GstElement * sink, GstCaps * caps)
{
  GstPad *sinkpad;

  if ((sinkpad = gst_element_get_static_pad (sink, "sink"))) {


    if (!gst_pad_query_accept_caps (sinkpad, caps)) {
      gst_object_unref (sinkpad);
      return FALSE;
    }
    gst_object_unref (sinkpad);
  }

  return TRUE;
}
