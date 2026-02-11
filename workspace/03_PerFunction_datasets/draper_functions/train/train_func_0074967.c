_gnutls_set_psk_session_key (gnutls_session_t session,
    gnutls_datum_t * ppsk ,
    gnutls_datum_t * dh_secret)
{
  gnutls_datum_t pwd_psk = { NULL, 0 };
  size_t dh_secret_size;
  int ret;

  if (session->security_parameters.entity == GNUTLS_SERVER)
    {
      psk_auth_info_t info;

      info = _gnutls_get_auth_info (session);


      ret = _gnutls_psk_pwd_find_entry (session, info->username, &pwd_psk);
      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }
      ppsk = &pwd_psk;
    }


  if (dh_secret == NULL)
    dh_secret_size = ppsk->size;
  else
    dh_secret_size = dh_secret->size;


  session->key->key.size = 4 + dh_secret_size + ppsk->size;
  session->key->key.data = gnutls_malloc (session->key->key.size);
  if (session->key->key.data == NULL)
    {
      gnutls_assert ();
      ret = GNUTLS_E_MEMORY_ERROR;
      goto error;
    }


  _gnutls_write_uint16 (dh_secret_size, session->key->key.data);
  if (dh_secret == NULL)
    memset (&session->key->key.data[2], 0, dh_secret_size);
  else
    memcpy (&session->key->key.data[2], dh_secret->data, dh_secret->size);
  _gnutls_write_datum16 (&session->key->key.data[dh_secret_size + 2], *ppsk);

  ret = 0;

error:
  _gnutls_free_datum (&pwd_psk);
  return ret;
}
