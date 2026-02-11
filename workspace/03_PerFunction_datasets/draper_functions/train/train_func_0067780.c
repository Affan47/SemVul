payload_type_change (GstElement * element, guint pt, GstRtpBinSession * session)
{
  GST_DEBUG_OBJECT (session->bin,
      "emiting signal for pt type changed to %d in session %d", pt,
      session->id);

  g_signal_emit (session->bin, gst_rtp_bin_signals[SIGNAL_PAYLOAD_TYPE_CHANGE],
      0, session->id, pt);
}
