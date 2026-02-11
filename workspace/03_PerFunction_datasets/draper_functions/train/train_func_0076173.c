gst_check_teardown_pad_by_name (GstElement * element, const gchar * name)
{
  GstPad *pad_peer, *pad_element;


  pad_element = gst_element_get_static_pad (element, name);


  pad_peer = gst_pad_get_peer (pad_element);

  if (pad_peer) {
    if (gst_pad_get_direction (pad_element) == GST_PAD_SINK)
      gst_pad_unlink (pad_peer, pad_element);
    else
      gst_pad_unlink (pad_element, pad_peer);
  }


  ASSERT_OBJECT_REFCOUNT (pad_element, "element pad_element", 2);
  gst_object_unref (pad_element);


  if (pad_peer) {

    ASSERT_OBJECT_REFCOUNT (pad_peer, "check pad_peer", 2);
    gst_object_unref (pad_peer);
    gst_object_unref (pad_peer);
  }
}
