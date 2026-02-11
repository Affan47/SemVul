gst_sdp_demux_configure_manager (GstSDPDemux * demux, char *rtsp_sdp)
{

  if (rtsp_sdp != NULL) {
    if (!(demux->session = gst_element_factory_make ("rtspsrc", NULL)))
      goto rtspsrc_failed;

    g_object_set (demux->session, "location", rtsp_sdp, NULL);

    GST_DEBUG_OBJECT (demux, "connect to signals on rtspsrc");
    demux->session_sig_id =
        g_signal_connect (demux->session, "pad-added",
        (GCallback) rtsp_session_pad_added, demux);
    demux->session_nmp_id =
        g_signal_connect (demux->session, "no-more-pads",
        (GCallback) rtsp_session_no_more_pads, demux);
  } else {
    if (!(demux->session = gst_element_factory_make ("rtpbin", NULL)))
      goto manager_failed;


    GST_DEBUG_OBJECT (demux, "connect to signals on session manager");
    demux->session_sig_id =
        g_signal_connect (demux->session, "pad-added",
        (GCallback) new_session_pad, demux);
    demux->session_ptmap_id =
        g_signal_connect (demux->session, "request-pt-map",
        (GCallback) request_pt_map, demux);
    g_signal_connect (demux->session, "on-bye-ssrc", (GCallback) on_bye_ssrc,
        demux);
    g_signal_connect (demux->session, "on-bye-timeout", (GCallback) on_timeout,
        demux);
    g_signal_connect (demux->session, "on-timeout", (GCallback) on_timeout,
        demux);
  }

  g_object_set (demux->session, "latency", demux->latency, NULL);


  gst_bin_add (GST_BIN_CAST (demux), demux->session);

  return TRUE;


manager_failed:
  {
    GST_DEBUG_OBJECT (demux, "no session manager element gstrtpbin found");
    return FALSE;
  }
rtspsrc_failed:
  {
    GST_DEBUG_OBJECT (demux, "no manager element rtspsrc found");
    return FALSE;
  }
}
