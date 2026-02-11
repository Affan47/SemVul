gst_rtspsrc_connection_receive (GstRTSPSrc * src, GstRTSPConnection * conn,
    GstRTSPMessage * message, GTimeVal * timeout)
{
  GstRTSPResult ret;

  if (conn)
    ret = gst_rtsp_connection_receive (conn, message, timeout);
  else
    ret = GST_RTSP_ERROR;

  return ret;
}
