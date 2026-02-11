gst_qt_mux_handle_buffer (GstCollectPads * pads, GstCollectData * cdata,
    GstBuffer * buf, gpointer user_data)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstQTMux *qtmux = GST_QT_MUX_CAST (user_data);
  GstQTPad *best_pad = NULL;
  GstClockTime best_time = GST_CLOCK_TIME_NONE;

  if (G_UNLIKELY (qtmux->state == GST_QT_MUX_STATE_STARTED)) {
    if ((ret = gst_qt_mux_start_file (qtmux)) != GST_FLOW_OK)
      return ret;
    else
      qtmux->state = GST_QT_MUX_STATE_DATA;
  }

  if (G_UNLIKELY (qtmux->state == GST_QT_MUX_STATE_EOS))
    return GST_FLOW_EOS;

  best_pad = (GstQTPad *) cdata;


  if (best_pad != NULL) {
    g_assert (buf);
    best_time = GST_BUFFER_PTS (buf);
    GST_LOG_OBJECT (qtmux, "selected pad %s with time %" GST_TIME_FORMAT,
        GST_PAD_NAME (best_pad->collect.pad), GST_TIME_ARGS (best_time));
    ret = gst_qt_mux_add_buffer (qtmux, best_pad, buf);
  } else {
    ret = gst_qt_mux_stop_file (qtmux);
    if (ret == GST_FLOW_OK) {
      GST_DEBUG_OBJECT (qtmux, "Pushing eos");
      gst_pad_push_event (qtmux->srcpad, gst_event_new_eos ());
      ret = GST_FLOW_EOS;
    } else {
      GST_WARNING_OBJECT (qtmux, "Failed to stop file: %s",
          gst_flow_get_name (ret));
    }
    qtmux->state = GST_QT_MUX_STATE_EOS;
  }

  return ret;
}
