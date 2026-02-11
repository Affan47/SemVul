_gnutls_handshake_client (gnutls_session_t session)
{
  int ret = 0;

#ifdef HANDSHAKE_DEBUG
  char buf[64];

  if (session->internals.resumed_security_parameters.session_id_size > 0)
    _gnutls_handshake_log ("HSK[%p]: Ask to resume: %s\n", session,
                           _gnutls_bin2hex (session->
                                            internals.resumed_security_parameters.session_id,
                                            session->
                                            internals.resumed_security_parameters.session_id_size,
                                            buf, sizeof (buf), NULL));
#endif

  switch (STATE)
    {
    case STATE0:
    case STATE1:
      ret = _gnutls_send_hello (session, AGAIN (STATE1));
      STATE = STATE1;
      IMED_RET ("send hello", ret, 1);

    case STATE2:

      ret =
        _gnutls_recv_handshake (session, NULL, NULL,
                                GNUTLS_HANDSHAKE_SERVER_HELLO,
                                MANDATORY_PACKET);
      STATE = STATE2;
      IMED_RET ("recv hello", ret, 1);

    case STATE70:
      if (session->security_parameters.do_recv_supplemental)
        {
          ret = _gnutls_recv_supplemental (session);
          STATE = STATE70;
          IMED_RET ("recv supplemental", ret, 1);
        }

    case STATE3:

      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_recv_server_certificate (session);
      STATE = STATE3;
      IMED_RET ("recv server certificate", ret, 1);

    case STATE4:

      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_recv_server_kx_message (session);
      STATE = STATE4;
      IMED_RET ("recv server kx message", ret, 1);

    case STATE5:


      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_recv_server_certificate_request (session);
      STATE = STATE5;
      IMED_RET ("recv server certificate request message", ret, 1);

    case STATE6:

      if (session->internals.resumed == RESUME_FALSE)
        ret =
          _gnutls_recv_handshake (session, NULL, NULL,
                                  GNUTLS_HANDSHAKE_SERVER_HELLO_DONE,
                                  MANDATORY_PACKET);
      STATE = STATE6;
      IMED_RET ("recv server hello done", ret, 1);

    case STATE71:
      if (session->security_parameters.do_send_supplemental)
        {
          ret = _gnutls_send_supplemental (session, AGAIN (STATE71));
          STATE = STATE71;
          IMED_RET ("send supplemental", ret, 0);
        }

    case STATE7:


      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_send_client_certificate (session, AGAIN (STATE7));
      STATE = STATE7;
      IMED_RET ("send client certificate", ret, 0);

    case STATE8:
      if (session->internals.resumed == RESUME_FALSE)
        ret = _gnutls_send_client_kx_message (session, AGAIN (STATE8));
      STATE = STATE8;
      IMED_RET ("send client kx", ret, 0);

    case STATE9:

      if (session->internals.resumed == RESUME_FALSE)
        ret =
          _gnutls_send_client_certificate_verify (session, AGAIN (STATE9));
      STATE = STATE9;
      IMED_RET ("send client certificate verify", ret, 1);

      STATE = STATE0;
    default:
      break;
    }


  return 0;
}
