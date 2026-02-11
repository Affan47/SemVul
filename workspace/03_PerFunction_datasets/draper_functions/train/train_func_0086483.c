gst_mve_mux_change_state (GstElement * element, GstStateChange transition)
{
  GstMveMux *mvemux;

  g_return_val_if_fail (GST_IS_MVE_MUX (element), GST_STATE_CHANGE_FAILURE);

  mvemux = GST_MVE_MUX (element);

  if (GST_ELEMENT_CLASS (parent_class)->change_state) {
    GstStateChangeReturn ret;

    ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
    if (ret != GST_STATE_CHANGE_SUCCESS)
      return ret;
  }

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_mve_mux_reset (mvemux);
      break;
    default:
      break;
  }

  return GST_STATE_CHANGE_SUCCESS;
}
