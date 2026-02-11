_gnutls_handshake_server (gnutls_session_t session)
{
  int ret = 0;

  switch (STATE)
    {
    case STATE0:
    case STATE1:
      ret =
        _gnutls_recv_handshake (session, NULL, NULL,
                                GNUTLS_HANDSHAKE_CLIENT_HELLO,
                                MANDATORY_PACKET);
      STATE = STATE1;
      IMED_RET ("recv hello", ret, 1);

    case STATE2:
      ret = _gnutls_send_hello (session, AGAIN (STATE2));
      STATE = STATE2;
      IMED_RET ("send hello", ret, 1);

    case STATE70:
      if (session->security_parameters.do_send_supplemental)
        {
          ret = _gnutls_send_supplemental (session, AGAIN (STATE70));
          STATE = STATE70;
          IMED_RET ("send supplemental data", ret, 0);
        }


    case STATE3:


      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_send_server_certificate (session, AGAIN (STATE3));
      STATE = STATE3;
      IMED_RET ("send server certificate", ret, 0);

    case STATE4:

      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_send_server_kx_message (session, AGAIN (STATE4));
      STATE = STATE4;
      IMED_RET ("send server kx", ret, 0);

    case STATE5:

      if (session->internals.resumed == RESUME_FALSE)
        ret =
          _gnutls_send_server_certificate_request (session, AGAIN (STATE5));
      STATE = STATE5;
      IMED_RET ("send server cert request", ret, 0);

    case STATE6:

      if (session->internals.resumed == RESUME_FALSE)
        ret =
          _gnutls_send_empty_handshake (session,
                                        GNUTLS_HANDSHAKE_SERVER_HELLO_DONE,
                                        AGAIN (STATE6));
      STATE = STATE6;
      IMED_RET ("send server hello done", ret, 1);

    case STATE71:
      if (session->security_parameters.do_recv_supplemental)
        {
          ret = _gnutls_recv_supplemental (session);
          STATE = STATE71;
          IMED_RET ("recv client supplemental", ret, 1);
        }


    case STATE7:

      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_recv_client_certificate (session);
      STATE = STATE7;
      IMED_RET ("recv client certificate", ret, 1);

    case STATE8:

      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_recv_client_kx_message (session);
      STATE = STATE8;
      IMED_RET ("recv client kx", ret, 1);

    case STATE9:

      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_recv_client_certificate_verify_message (session);
      STATE = STATE9;
      IMED_RET ("recv client certificate verify", ret, 1);

      STATE = STATE0;
    default:
      break;
    }

  return 0;
}
