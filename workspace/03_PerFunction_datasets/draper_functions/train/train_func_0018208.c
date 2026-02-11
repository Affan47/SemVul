do_handshake (gnutls_session_t session)
{
  int ret;

  do
    {
      ret = gnutls_handshake (session);
      if (ret < 0)
        handle_error (session, ret);
    }
  while (ret < 0 && gnutls_error_is_fatal (ret) == 0);

  if (ret != 0)
    gnutls_alert_send_appropriate (session, ret);

  return ret;
}
