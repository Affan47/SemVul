gnutls_psk_netconf_derive_key (const char *password,
                               const char *psk_identity,
                               const char *psk_identity_hint,
                               gnutls_datum_t * output_key)
{
  const char netconf_key_pad[] = "Key Pad for Netconf";
  size_t sha1len = _gnutls_hash_get_algo_len (GNUTLS_DIG_SHA1);
  size_t hintlen = strlen (psk_identity_hint);
  digest_hd_st dig;
  char *inner;
  size_t innerlen;
  int rc;


  rc = _gnutls_hash_init (&dig, GNUTLS_DIG_SHA1);
  if (rc < 0)
    {
      gnutls_assert ();
      return rc;
    }

  rc = _gnutls_hash (&dig, psk_identity, strlen (psk_identity));
  if (rc < 0)
    {
      gnutls_assert ();
      _gnutls_hash_deinit (&dig, NULL);
      return rc;
    }

  rc = _gnutls_hash (&dig, netconf_key_pad, strlen (netconf_key_pad));
  if (rc < 0)
    {
      gnutls_assert ();
      _gnutls_hash_deinit (&dig, NULL);
      return rc;
    }

  rc = _gnutls_hash (&dig, password, strlen (password));
  if (rc < 0)
    {
      gnutls_assert ();
      _gnutls_hash_deinit (&dig, NULL);
      return rc;
    }

  innerlen = sha1len + hintlen;
  inner = gnutls_malloc (innerlen);
  _gnutls_hash_deinit (&dig, inner);
  if (inner == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  memcpy (inner + sha1len, psk_identity_hint, hintlen);

  rc = _gnutls_hash_init (&dig, GNUTLS_DIG_SHA1);
  if (rc < 0)
    {
      gnutls_assert ();
      gnutls_free (inner);
      return rc;
    }

  rc = _gnutls_hash (&dig, inner, innerlen);
  gnutls_free (inner);
  if (rc < 0)
    {
      gnutls_assert ();
      _gnutls_hash_deinit (&dig, NULL);
      return rc;
    }

  output_key->data = gnutls_malloc (sha1len);
  _gnutls_hash_deinit (&dig, output_key->data);
  if (output_key->data == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }
  output_key->size = sha1len;

  return 0;
}
