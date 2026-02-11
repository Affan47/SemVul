rtp_session_send_rtp (RTPSession * sess, gpointer data, gboolean is_list,
    GstClockTime current_time, GstClockTime running_time)
{
  GstFlowReturn result;
  RTPSource *source;
  gboolean prevsender;
  guint64 oldrate;
  RTPPacketInfo pinfo = { 0, };
  gboolean created;

  g_return_val_if_fail (RTP_IS_SESSION (sess), GST_FLOW_ERROR);
  g_return_val_if_fail (is_list || GST_IS_BUFFER (data), GST_FLOW_ERROR);

  GST_LOG ("received RTP %s for sending", is_list ? "list" : "packet");

  RTP_SESSION_LOCK (sess);
  if (!update_packet_info (sess, &pinfo, TRUE, TRUE, is_list, data,
          current_time, running_time, -1))
    goto invalid_packet;

  source = obtain_internal_source (sess, pinfo.ssrc, &created);


  source->last_rtp_activity = current_time;

  prevsender = RTP_SOURCE_IS_SENDER (source);
  oldrate = source->bitrate;


  result = rtp_source_send_rtp (source, &pinfo);

  source_update_sender (sess, source, prevsender);

  if (oldrate != source->bitrate)
    sess->recalc_bandwidth = TRUE;
  RTP_SESSION_UNLOCK (sess);

  g_object_unref (source);
  clean_packet_info (&pinfo);

  return result;

invalid_packet:
  {
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));
    RTP_SESSION_UNLOCK (sess);
    GST_DEBUG ("invalid RTP packet received");
    return GST_FLOW_OK;
  }
}
