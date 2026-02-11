handle_unauthorized_request (GstRTSPClient * client, GstRTSPAuth * auth,
    GstRTSPClientState * state)
{
  gst_rtsp_message_init_response (state->response, GST_RTSP_STS_UNAUTHORIZED,
      gst_rtsp_status_as_text (GST_RTSP_STS_UNAUTHORIZED), state->request);

  if (auth) {

    gst_rtsp_auth_setup_auth (auth, client, 0, state);
  }

  send_response (client, state->session, state->response);
}
