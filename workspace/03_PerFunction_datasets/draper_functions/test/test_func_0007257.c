try_element (GstElement * bin, GstElement * element)
{
  GstStateChangeReturn ret;

  if (element) {
    ret = gst_element_set_state (element, GST_STATE_READY);
    if (ret == GST_STATE_CHANGE_FAILURE) {
      GST_DEBUG_OBJECT (bin, "failed state change..");
      gst_element_set_state (element, GST_STATE_NULL);
      gst_object_unref (element);
      element = NULL;
    }
  }
  return element;
}
