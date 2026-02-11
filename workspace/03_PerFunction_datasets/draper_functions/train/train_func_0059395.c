ccm_aead_init(gcry_cipher_hd_t hd, size_t buflen, int authlen)
{
  const int _L = 4;
  const int noncelen = 15 - _L;
  char nonce[noncelen];
  u64 params[3];
  gcry_error_t err = GPG_ERR_NO_ERROR;

  memset (nonce, 0x33, noncelen);

  err = gcry_cipher_setiv (hd, nonce, noncelen);
  if (err)
    {
      fprintf (stderr, "gcry_cipher_setiv failed: %s\n",
               gpg_strerror (err));
      gcry_cipher_close (hd);
      exit (1);
    }

  params[0] = buflen;
  params[1] = 0;
  params[2] = authlen;
  err = gcry_cipher_ctl (hd, GCRYCTL_SET_CCM_LENGTHS, params, sizeof(params));
  if (err)
    {
      fprintf (stderr, "gcry_cipher_setiv failed: %s\n",
               gpg_strerror (err));
      gcry_cipher_close (hd);
      exit (1);
    }
}
