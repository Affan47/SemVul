eme_pkcs_v1_5_encode (unsigned int flags, void *opts,
		      gcry_ac_io_t *ac_io_read,
		      gcry_ac_io_t *ac_io_write)
{
  gcry_ac_eme_pkcs_v1_5_t *options;
  gcry_error_t err;
  unsigned char *buffer;
  unsigned char *ps;
  unsigned char *m;
  size_t m_n;
  unsigned int ps_n;
  unsigned int k;

  (void)flags;

  options = opts;
  buffer = NULL;
  m = NULL;

  err = _gcry_ac_io_read_all (ac_io_read, &m, &m_n);
  if (err)
    goto out;


  k = options->key_size / 8;

  if (m_n > k - 11)
    {

      err = gcry_error (GPG_ERR_TOO_SHORT);
      goto out;
    }


  buffer = gcry_malloc (k - 1);
  if (! buffer)
    {
      err = gcry_error_from_errno (errno);
      goto out;
    }


  ps_n = k - m_n - 3;
  ps = buffer + 1;
  em_randomize_nonzero (ps, ps_n, GCRY_STRONG_RANDOM);


  buffer[0] = 0x02;
  buffer[ps_n + 1] = 0x00;
  memcpy (buffer + ps_n + 2, m, m_n);

  err = _gcry_ac_io_write (ac_io_write, buffer, k - 1);

 out:

  gcry_free (buffer);
  gcry_free (m);

  return err;
}
