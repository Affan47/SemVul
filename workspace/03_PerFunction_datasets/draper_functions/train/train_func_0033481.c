_gnutls_handshake_hash_add_sent (gnutls_session_t session,
                                 gnutls_handshake_description_t type,
                                 opaque * dataptr, uint32_t datalen)
{
  int ret;

  if (session->security_parameters.entity == GNUTLS_CLIENT
      && type == GNUTLS_HANDSHAKE_CLIENT_HELLO)
    {

      if ((ret =
           _gnutls_handshake_buffer_put (session, dataptr, datalen)) < 0)
        {
          gnutls_assert ();
          return ret;
        }
      return 0;
    }

  if ((ret = _gnutls_handshake_hash_pending (session)) < 0)
    {
      gnutls_assert ();
      return ret;
    }

  if (type != GNUTLS_HANDSHAKE_HELLO_REQUEST)
    {
      if (session->security_parameters.handshake_mac_handle_type ==
          HANDSHAKE_MAC_TYPE_10)
        {
          _gnutls_hash (&session->internals.handshake_mac_handle.tls10.sha,
                        dataptr, datalen);
          _gnutls_hash (&session->internals.handshake_mac_handle.tls10.md5,
                        dataptr, datalen);
        }
      else if (session->security_parameters.handshake_mac_handle_type ==
               HANDSHAKE_MAC_TYPE_12)
        {
          _gnutls_hash (&session->internals.handshake_mac_handle.tls12.sha256,
                        dataptr, datalen);
          _gnutls_hash (&session->internals.handshake_mac_handle.tls12.sha1,
                        dataptr, datalen);
        }
    }

  return 0;
}
