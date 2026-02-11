gnutls_bye (gnutls_session_t session, gnutls_close_request_t how)
{
  int ret = 0;

  switch (STATE)
    {
    case STATE0:
    case STATE60:
      ret = _gnutls_io_write_flush (session);
      STATE = STATE60;
      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }

    case STATE61:
      ret =
        gnutls_alert_send (session, GNUTLS_AL_WARNING, GNUTLS_A_CLOSE_NOTIFY);
      STATE = STATE61;
      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }

    case STATE62:
      STATE = STATE62;
      if (how == GNUTLS_SHUT_RDWR)
        {
          do
            {
              _gnutls_io_clear_peeked_data (session);
              ret = _gnutls_recv_int (session, GNUTLS_ALERT, -1, NULL, 0);
            }
          while (ret == GNUTLS_E_GOT_APPLICATION_DATA);

          if (ret >= 0)
            session->internals.may_not_read = 1;

          if (ret < 0)
            {
              gnutls_assert ();
              return ret;
            }
        }
      STATE = STATE62;

      break;
    default:
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  STATE = STATE0;

  session->internals.may_not_write = 1;
  return 0;
}
