gst_dvd_spu_change_state (GstElement * element, GstStateChange transition)
{
  GstDVDSpu *dvdspu = (GstDVDSpu *) element;
  GstStateChangeReturn ret;

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      DVD_SPU_LOCK (dvdspu);
      gst_dvd_spu_clear (dvdspu);
      DVD_SPU_UNLOCK (dvdspu);
      break;
    default:
      break;
  }

  return ret;
}
