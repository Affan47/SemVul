proc_psk_client_kx (gnutls_session_t session, opaque * data,
                    size_t _data_size)
{
  int ret;
  bigint_t p, g;
  gnutls_dh_params_t dh_params;
  const bigint_t *mpis;
  gnutls_psk_server_credentials_t cred;
  psk_auth_info_t info;
  gnutls_datum_t username;
  ssize_t data_size = _data_size;

  cred = (gnutls_psk_server_credentials_t)
    _gnutls_get_cred (session->key, GNUTLS_CRD_PSK, NULL);

  if (cred == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INSUFFICIENT_CREDENTIALS;
    }

  if ((ret =
       _gnutls_auth_info_set (session, GNUTLS_CRD_PSK,
                              sizeof (psk_auth_info_st), 1)) < 0)
    {
      gnutls_assert ();
      return ret;
    }

  dh_params =
    _gnutls_get_dh_params (cred->dh_params, cred->params_func, session);
  mpis = _gnutls_dh_params_to_mpi (dh_params);
  if (mpis == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_NO_TEMPORARY_DH_PARAMS;
    }

  p = mpis[0];
  g = mpis[1];

  DECR_LEN (data_size, 2);
  username.size = _gnutls_read_uint16 (&data[0]);

  DECR_LEN (data_size, username.size);

  username.data = &data[2];


  info = _gnutls_get_auth_info (session);

  if (username.size > MAX_USERNAME_SIZE)
    {
      gnutls_assert ();
      return GNUTLS_E_ILLEGAL_SRP_USERNAME;
    }

  memcpy (info->username, username.data, username.size);
  info->username[username.size] = 0;


  data += username.size + 2;

  ret = _gnutls_proc_dh_common_client_kx (session, data, data_size, g, p);

  return ret;

}
