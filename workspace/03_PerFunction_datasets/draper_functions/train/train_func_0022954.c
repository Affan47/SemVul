gst_rtsp_wms_after_send (GstRTSPExtension * ext, GstRTSPMessage * req,
    GstRTSPMessage * resp)
{
  GstRTSPWMS *ctx = (GstRTSPWMS *) ext;

  GST_DEBUG_OBJECT (ext, "after send");

  switch (req->type_data.request.method) {
    case GST_RTSP_OPTIONS:
    {
      gchar *server = NULL;

      gst_rtsp_message_get_header (resp, GST_RTSP_HDR_SERVER, &server, 0);
      if (server && g_str_has_prefix (server, SERVER_PREFIX))
        ctx->active = TRUE;
      else
        ctx->active = FALSE;
      break;
    }
    default:
      break;
  }
  return GST_RTSP_OK;
}
