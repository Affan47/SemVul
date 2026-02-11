gnutls_openpgp_crt_get_pk_rsa_raw (gnutls_openpgp_crt_t crt,
                                   gnutls_datum_t * m, gnutls_datum_t * e)
{
  uint8_t keyid[GNUTLS_OPENPGP_KEYID_SIZE];
  int ret;

  ret = gnutls_openpgp_crt_get_key_id (crt, keyid);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  return _get_pk_rsa_raw (crt, keyid, m, e);
}
