_gcry_ac_data_encrypt_scheme (gcry_ac_handle_t handle,
			      gcry_ac_scheme_t scheme_id,
			      unsigned int flags, void *opts,
			      gcry_ac_key_t key,
			      gcry_ac_io_t *io_message,
			      gcry_ac_io_t *io_cipher)
{
  gcry_error_t err;
  gcry_ac_io_t io_em;
  unsigned char *em;
  size_t em_n;
  gcry_mpi_t mpi_plain;
  gcry_ac_data_t data_encrypted;
  gcry_mpi_t mpi_encrypted;
  unsigned char *buffer;
  size_t buffer_n;
  void *opts_em;
  ac_scheme_t *scheme;

  (void)flags;

  if (fips_mode ())
    return gpg_error (GPG_ERR_NOT_SUPPORTED);

  data_encrypted = NULL;
  mpi_encrypted = NULL;
  mpi_plain = NULL;
  opts_em = NULL;
  buffer = NULL;
  em = NULL;

  scheme = ac_scheme_get (scheme_id);
  if (! scheme)
    {
      err = gcry_error (GPG_ERR_NO_ENCRYPTION_SCHEME);
      goto out;
    }

  if (key->type != GCRY_AC_KEY_PUBLIC)
    {
      err = gcry_error (GPG_ERR_WRONG_KEY_USAGE);
      goto out;
    }

  err = ac_dencode_prepare (handle, key, opts, *scheme, &opts_em);
  if (err)
    goto out;

  _gcry_ac_io_init (&io_em, GCRY_AC_IO_WRITABLE,
		    GCRY_AC_IO_STRING, &em, &em_n);

  err = _gcry_ac_data_encode (scheme->scheme_encoding, 0, opts_em,
			      io_message, &io_em);
  if (err)
    goto out;

  mpi_plain = gcry_mpi_snew (0);
  gcry_ac_os_to_mpi (mpi_plain, em, em_n);

  err = _gcry_ac_data_encrypt (handle, 0, key, mpi_plain, &data_encrypted);
  if (err)
    goto out;

  err = ac_data_set_to_mpi (data_encrypted, &mpi_encrypted);
  if (err)
    goto out;

  err = _gcry_ac_mpi_to_os_alloc (mpi_encrypted, &buffer, &buffer_n);
  if (err)
    goto out;

  err = _gcry_ac_io_write (io_cipher, buffer, buffer_n);

 out:

  gcry_ac_data_destroy (data_encrypted);
  gcry_mpi_release (mpi_encrypted);
  gcry_mpi_release (mpi_plain);
  gcry_free (opts_em);
  gcry_free (buffer);
  gcry_free (em);

  return err;
}
