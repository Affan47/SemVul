_gnutls_write_connection_state_init (gnutls_session_t session)
{
  const uint16_t epoch_next = session->security_parameters.epoch_next;
  int ret;


  if (session->internals.resumed == RESUME_FALSE)
    {
      ret = _gnutls_check_algos (session,
                                 &session->
                                 security_parameters.current_cipher_suite,
                                 session->internals.compression_method);
      if (ret < 0)
        return ret;

      ret = _gnutls_set_kx (session,
                            _gnutls_cipher_suite_get_kx_algo
                            (&session->
                             security_parameters.current_cipher_suite));
      if (ret < 0)
        return ret;
    }
  else if (session->security_parameters.entity == GNUTLS_SERVER)
    _gnutls_set_resumed_parameters (session);

  ret = _gnutls_epoch_set_keys (session, epoch_next);
  if (ret < 0)
    return gnutls_assert_val (ret);

  _gnutls_handshake_log ("HSK[%p]: Cipher Suite: %s\n", session,
                         _gnutls_cipher_suite_get_name
                         (&session->
                          security_parameters.current_cipher_suite));

  _gnutls_handshake_log
    ("HSK[%p]: Initializing internal [write] cipher sessions\n", session);

  session->security_parameters.epoch_write = epoch_next;
  _gnutls_epoch_gc (session);

  return 0;
}
