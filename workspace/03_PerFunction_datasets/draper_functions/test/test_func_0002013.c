gst_rtp_session_query_send_rtcp_src (GstPad * pad, GstQuery * query)
{
  GstRtpSession *rtpsession;
  gboolean ret = FALSE;

  rtpsession = GST_RTP_SESSION (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT (rtpsession, "received QUERY");

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_LATENCY:
      ret = TRUE;

      gst_query_set_latency (query, FALSE, 0, -1);
      break;
    default:

      break;
  }

  gst_object_unref (rtpsession);

  return ret;
}
