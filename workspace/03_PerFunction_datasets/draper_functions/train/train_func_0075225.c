remove_recv_rtcp (GstRtpBin * rtpbin, GstRtpBinSession * session)
{
  if (session->recv_rtcp_sink_ghost) {
    gst_pad_set_active (session->recv_rtcp_sink_ghost, FALSE);
    gst_element_remove_pad (GST_ELEMENT_CAST (rtpbin),
        session->recv_rtcp_sink_ghost);
    session->recv_rtcp_sink_ghost = NULL;
  }
  if (session->sync_src) {

    gst_object_unref (session->sync_src);
    session->sync_src = NULL;
  }
  if (session->recv_rtcp_sink) {
    gst_element_release_request_pad (session->session, session->recv_rtcp_sink);
    gst_object_unref (session->recv_rtcp_sink);
    session->recv_rtcp_sink = NULL;
  }
}
