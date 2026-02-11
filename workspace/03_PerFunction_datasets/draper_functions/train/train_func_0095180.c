gst_rtspsrc_handle_request (GstRTSPSrc * src, GstRTSPConnection * conn,
    GstRTSPMessage * request)
{
  GstRTSPMessage response = { 0 };
  GstRTSPResult res;

  GST_DEBUG_OBJECT (src, "got server request message");

  if (src->debug)
    gst_rtsp_message_dump (request);

  res = gst_rtsp_ext_list_receive_request (src->extensions, request);

  if (res == GST_RTSP_ENOTIMPL) {

    GST_DEBUG_OBJECT (src, "prepare OK reply");
    res =
        gst_rtsp_message_init_response (&response, GST_RTSP_STS_OK, "OK",
        request);
    if (res < 0)
      goto send_error;


    g_signal_emit (src, gst_rtspsrc_signals[SIGNAL_HANDLE_REQUEST],
        0, request, &response);

    if (src->debug)
      gst_rtsp_message_dump (&response);

    res = gst_rtspsrc_connection_send (src, conn, &response, NULL);
    if (res < 0)
      goto send_error;

    gst_rtsp_message_unset (&response);
  } else if (res == GST_RTSP_EEOF)
    return res;

  return GST_RTSP_OK;


send_error:
  {
    gst_rtsp_message_unset (&response);
    return res;
  }
}
