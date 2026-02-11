_gnutls_peers_cert_less_512 (gnutls_session_t session)
{
  gnutls_cert peer_cert;
  int ret;
  cert_auth_info_t info = _gnutls_get_auth_info (session);

  if (info == NULL || info->ncerts == 0)
    {
      gnutls_assert ();

      return 0;
    }

  if ((ret =
       _gnutls_get_auth_info_gcert (&peer_cert,
                                    session->security_parameters.cert_type,
                                    info, CERT_NO_COPY)) < 0)
    {
      gnutls_assert ();
      return 0;
    }

  if (peer_cert.subject_pk_algorithm != GNUTLS_PK_RSA)
    {
      gnutls_assert ();
      _gnutls_gcert_deinit (&peer_cert);
      return 0;
    }

  if (_gnutls_mpi_get_nbits (peer_cert.params[0]) <= 512)
    {
      _gnutls_gcert_deinit (&peer_cert);
      return 1;
    }

  _gnutls_gcert_deinit (&peer_cert);

  return 0;
}
