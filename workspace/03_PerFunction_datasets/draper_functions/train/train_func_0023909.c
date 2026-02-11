gst_rtp_session_event_recv_rtcp_sink (GstPad * pad, GstEvent * event)
{
  GstRtpSession *rtpsession;
  gboolean ret = FALSE;

  rtpsession = GST_RTP_SESSION (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT (rtpsession, "received event %s",
      GST_EVENT_TYPE_NAME (event));

  switch (GST_EVENT_TYPE (event)) {
    default:
      ret = gst_pad_push_event (rtpsession->sync_src, event);
      break;
  }
  gst_object_unref (rtpsession);

  return ret;
}
