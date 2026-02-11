gst_rtsp_conninfo_reconnect (GstRTSPSrc * src, GstRTSPConnInfo * info,
    gboolean async)
{
  GstRTSPResult res;

  GST_DEBUG_OBJECT (src, "reconnecting connection...");
  gst_rtsp_conninfo_close (src, info, FALSE);
  res = gst_rtsp_conninfo_connect (src, info, async);

  return res;
}
