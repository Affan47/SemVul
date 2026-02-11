_gnutls_openpgp_request_key (gnutls_session_t session, gnutls_datum_t * ret,
                             const gnutls_certificate_credentials_t cred,
                             opaque * key_fpr, int key_fpr_size)
{
  int rc = 0;

  if (!ret || !cred || !key_fpr)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  if (key_fpr_size != 16 && key_fpr_size != 20)
    return GNUTLS_E_HASH_FAILED;

  rc = gnutls_openpgp_get_key (ret, cred->keyring, KEY_ATTR_FPR, key_fpr);

  if (rc >= 0)
    {
      rc = 0;
      goto error;
    }
  else
    rc = GNUTLS_E_OPENPGP_GETKEY_FAILED;


  if (session->internals.openpgp_recv_key_func != NULL)
    {
      rc = session->internals.openpgp_recv_key_func (session,
                                                     key_fpr,
                                                     key_fpr_size, ret);
      if (rc < 0)
        {
          gnutls_assert ();
          rc = GNUTLS_E_OPENPGP_GETKEY_FAILED;
          goto error;
        }
    }

error:

  return rc;
}
