gnutls_certificate_set_openpgp_keyring_mem (gnutls_certificate_credentials_t
                                            c, const opaque * data,
                                            size_t dlen,
                                            gnutls_openpgp_crt_fmt_t format)
{
  gnutls_datum_t ddata;
  int rc;

  ddata.data = (void *) data;
  ddata.size = dlen;

  if (!c || !data || !dlen)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  rc = gnutls_openpgp_keyring_init (&c->keyring);
  if (rc < 0)
    {
      gnutls_assert ();
      return rc;
    }

  rc = gnutls_openpgp_keyring_import (c->keyring, &ddata, format);
  if (rc < 0)
    {
      gnutls_assert ();
      gnutls_openpgp_keyring_deinit (c->keyring);
      return rc;
    }

  return 0;
}
