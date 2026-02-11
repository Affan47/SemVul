_gnutls_get_public_rsa_params (gnutls_session_t session,
                               bigint_t params[MAX_PUBLIC_PARAMS_SIZE],
                               int *params_len)
{
  int ret;
  cert_auth_info_t info;
  gnutls_cert peer_cert;
  int i;


  info = _gnutls_get_auth_info (session);

  if (info == NULL || info->ncerts == 0)
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  ret =
    _gnutls_get_auth_info_gcert (&peer_cert,
                                 session->security_parameters.cert_type,
                                 info, CERT_ONLY_PUBKEY | CERT_NO_COPY);

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }


  if (_gnutls_cipher_suite_get_kx_algo
      (&session->security_parameters.current_cipher_suite) ==
      GNUTLS_KX_RSA_EXPORT
      && _gnutls_mpi_get_nbits (peer_cert.params[0]) > 512)
    {

      _gnutls_gcert_deinit (&peer_cert);

      if (session->key->rsa[0] == NULL || session->key->rsa[1] == NULL)
        {
          gnutls_assert ();
          return GNUTLS_E_INTERNAL_ERROR;
        }

      if (*params_len < 2)
        {
          gnutls_assert ();
          return GNUTLS_E_INTERNAL_ERROR;
        }
      *params_len = 2;
      for (i = 0; i < *params_len; i++)
        {
          params[i] = _gnutls_mpi_copy (session->key->rsa[i]);
        }

      return 0;
    }


  if (*params_len < peer_cert.params_size)
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }
  *params_len = peer_cert.params_size;

  for (i = 0; i < *params_len; i++)
    {
      params[i] = _gnutls_mpi_copy (peer_cert.params[i]);
    }
  _gnutls_gcert_deinit (&peer_cert);

  return 0;
}
