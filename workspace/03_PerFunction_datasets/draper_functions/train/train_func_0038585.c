gst_rtsp_session_free_stream (GstRTSPSessionStream * stream)
{
  GST_INFO ("free session stream %p", stream);


  gst_rtsp_session_stream_set_callbacks (stream, NULL, NULL, NULL, NULL, NULL,
      NULL);
  gst_rtsp_session_stream_set_keepalive (stream, NULL, NULL, NULL);

  gst_rtsp_media_trans_cleanup (&stream->trans);

  g_free (stream);
}
