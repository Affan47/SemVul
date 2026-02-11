gnutls_certificate_set_openpgp_key (gnutls_certificate_credentials_t res,
                                    gnutls_openpgp_crt_t crt,
                                    gnutls_openpgp_privkey_t pkey)
{
  int ret;
  gnutls_privkey_t privkey;
  gnutls_cert *ccert;


  ret = gnutls_privkey_init (&privkey);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  ret =
    gnutls_privkey_import_openpgp (privkey, pkey,
                                   GNUTLS_PRIVKEY_IMPORT_COPY);
  if (ret < 0)
    {
      gnutls_privkey_deinit (privkey);
      gnutls_assert ();
      return ret;
    }


  ccert = gnutls_calloc (1, sizeof (gnutls_cert));
  if (ccert == NULL)
    {
      gnutls_assert ();
      gnutls_privkey_deinit (privkey);
      return GNUTLS_E_MEMORY_ERROR;
    }

  ret = _gnutls_openpgp_crt_to_gcert (ccert, crt);
  if (ret < 0)
    {
      gnutls_assert ();
      gnutls_free (ccert);
      gnutls_privkey_deinit (privkey);
      return ret;
    }

  ret = certificate_credentials_append_pkey (res, privkey);
  if (ret >= 0)
    ret = certificate_credential_append_crt_list (res, ccert, 1);

  if (ret < 0)
    {
      gnutls_assert ();
      gnutls_free (ccert);
      gnutls_privkey_deinit (privkey);
      return ret;
    }

  res->ncerts++;


  return 0;
}
