_gnutls_mac_init_ssl3 (digest_hd_st * ret, gnutls_mac_algorithm_t algorithm,
                       void *key, int keylen)
{
  opaque ipad[48];
  int padsize, result;

  padsize = get_padsize (algorithm);
  if (padsize == 0)
    {
      gnutls_assert ();
      return GNUTLS_E_HASH_FAILED;
    }

  memset (ipad, 0x36, padsize);

  result = _gnutls_hash_init (ret, algorithm);
  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  ret->key = key;
  ret->keysize = keylen;

  if (keylen > 0)
    _gnutls_hash (ret, key, keylen);
  _gnutls_hash (ret, ipad, padsize);

  return 0;
}
