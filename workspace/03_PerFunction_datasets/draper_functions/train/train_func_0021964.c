gst_rtp_mux_chain (GstPad * pad, GstObject * parent, GstBuffer * buffer)
{
  GstRTPMux *rtp_mux;
  GstFlowReturn ret;
  GstRTPMuxPadPrivate *padpriv;
  gboolean drop;
  gboolean changed = FALSE;
  GstRTPBuffer rtpbuffer = GST_RTP_BUFFER_INIT;

  rtp_mux = GST_RTP_MUX (GST_OBJECT_PARENT (pad));

  GST_OBJECT_LOCK (rtp_mux);
  padpriv = gst_pad_get_element_private (pad);

  if (!padpriv) {
    GST_OBJECT_UNLOCK (rtp_mux);
    gst_buffer_unref (buffer);
    return GST_FLOW_NOT_LINKED;
  }

  buffer = gst_buffer_make_writable (buffer);

  if (!gst_rtp_buffer_map (buffer, GST_MAP_READWRITE, &rtpbuffer)) {
    GST_OBJECT_UNLOCK (rtp_mux);
    gst_buffer_unref (buffer);
    GST_ERROR_OBJECT (rtp_mux, "Invalid RTP buffer");
    return GST_FLOW_ERROR;
  }

  drop = !process_buffer_locked (rtp_mux, padpriv, &rtpbuffer);

  gst_rtp_buffer_unmap (&rtpbuffer);

  if (!drop) {
    if (pad != rtp_mux->last_pad) {
      changed = TRUE;
      g_clear_object (&rtp_mux->last_pad);
      rtp_mux->last_pad = g_object_ref (pad);
    }

    if (GST_BUFFER_DURATION_IS_VALID (buffer) &&
        GST_BUFFER_TIMESTAMP_IS_VALID (buffer))
      rtp_mux->last_stop = GST_BUFFER_TIMESTAMP (buffer) +
          GST_BUFFER_DURATION (buffer);
    else
      rtp_mux->last_stop = GST_CLOCK_TIME_NONE;
  }

  GST_OBJECT_UNLOCK (rtp_mux);

  if (changed)
    gst_pad_sticky_events_foreach (pad, resend_events, rtp_mux);

  if (drop) {
    gst_buffer_unref (buffer);
    ret = GST_FLOW_OK;
  } else {
    ret = gst_pad_push (rtp_mux->srcpad, buffer);
  }

  return ret;
}
