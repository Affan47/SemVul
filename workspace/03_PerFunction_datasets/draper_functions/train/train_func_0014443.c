cipher_get_blocksize (int algorithm)
{
  gcry_module_t cipher;
  unsigned len = 0;

  REGISTER_DEFAULT_CIPHERS;

  ath_mutex_lock (&ciphers_registered_lock);
  cipher = _gcry_module_lookup_id (ciphers_registered, algorithm);
  if (cipher)
    {
      len = ((gcry_cipher_spec_t *) cipher->spec)->blocksize;
      if (! len)
	  log_bug ("cipher %d w/o blocksize\n", algorithm);
      _gcry_module_release (cipher);
    }
  ath_mutex_unlock (&ciphers_registered_lock);

  return len;
}
