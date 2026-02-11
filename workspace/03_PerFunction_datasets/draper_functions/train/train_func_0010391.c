gst_flv_demux_change_state (GstElement * element, GstStateChange transition)
{
  GstFlvDemux *demux;
  GstStateChangeReturn ret;

  demux = GST_FLV_DEMUX (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:


      if (demux->own_index) {
        gst_object_unref (demux->index);
        demux->index = NULL;
        demux->own_index = FALSE;
      }


      if (G_UNLIKELY (!demux->index)) {
        GST_DEBUG_OBJECT (demux, "no index provided creating our own");

        demux->index = gst_index_factory_make ("memindex");

        gst_index_get_writer_id (demux->index, GST_OBJECT (demux),
            &demux->index_id);
        demux->own_index = TRUE;
      }
      gst_flv_demux_cleanup (demux);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
  if (ret == GST_STATE_CHANGE_FAILURE)
    return ret;

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_flv_demux_cleanup (demux);
      break;
    default:
      break;
  }

  return ret;
}
