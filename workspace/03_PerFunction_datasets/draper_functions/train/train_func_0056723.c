rtp_session_set_send_rtcp_callback (RTPSession * sess,
    RTPSessionSendRTCP callback, gpointer user_data)
{
  g_return_if_fail (RTP_IS_SESSION (sess));

  sess->callbacks.send_rtcp = callback;
  sess->send_rtcp_user_data = user_data;
}
