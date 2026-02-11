test_max_record_size (gnutls_session_t session)
{
  int ret;
  sprintf (prio_str,
           INIT_STR ALL_CIPHERS ":" ALL_COMP ":" ALL_CERTTYPES ":%s:" ALL_MACS
           ":" ALL_KX ":%s", protocol_str, rest);
  _gnutls_priority_set_direct (session, prio_str);
  gnutls_credentials_set (session, GNUTLS_CRD_CERTIFICATE, xcred);
  gnutls_record_set_max_size (session, 512);

  ret = do_handshake (session);
  if (ret == TEST_FAILED)
    return ret;

  ret = gnutls_record_get_max_size (session);
  if (ret == 512)
    return TEST_SUCCEED;

  return TEST_FAILED;
}
