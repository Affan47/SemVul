_gcry_ac_data_decrypt_scheme (gcry_ac_handle_t handle,
			      gcry_ac_scheme_t scheme_id,
			      unsigned int flags, void *opts,
			      gcry_ac_key_t key,
			      gcry_ac_io_t *io_cipher,
			      gcry_ac_io_t *io_message)
{
  gcry_ac_io_t io_em;
  gcry_error_t err;
  gcry_ac_data_t data_encrypted;
  unsigned char *em;
  size_t em_n;
  gcry_mpi_t mpi_encrypted;
  gcry_mpi_t mpi_decrypted;
  void *opts_em;
  ac_scheme_t *scheme;
  char *elements_enc;
  size_t elements_enc_n;
  unsigned char *c;
  size_t c_n;

  (void)flags;

  if (fips_mode ())
    return gpg_error (GPG_ERR_NOT_SUPPORTED);

  data_encrypted = NULL;
  mpi_encrypted = NULL;
  mpi_decrypted = NULL;
  elements_enc = NULL;
  opts_em = NULL;
  em = NULL;
  c = NULL;

  scheme = ac_scheme_get (scheme_id);
  if (! scheme)
    {
      err = gcry_error (GPG_ERR_NO_ENCRYPTION_SCHEME);
      goto out;
    }

  if (key->type != GCRY_AC_KEY_SECRET)
    {
      err = gcry_error (GPG_ERR_WRONG_KEY_USAGE);
      goto out;
    }

  err = _gcry_ac_io_read_all (io_cipher, &c, &c_n);
  if (err)
    goto out;

  mpi_encrypted = gcry_mpi_snew (0);
  gcry_ac_os_to_mpi (mpi_encrypted, c, c_n);

  err = _gcry_pk_get_elements (handle->algorithm, &elements_enc, NULL);
  if (err)
    goto out;

  elements_enc_n = strlen (elements_enc);
  if (elements_enc_n != 1)
    {

      err = gcry_error (GPG_ERR_CONFLICT);
      goto out;
    }

  err = _gcry_ac_data_new (&data_encrypted);
  if (err)
    goto out;

  err = _gcry_ac_data_set (data_encrypted, GCRY_AC_FLAG_COPY | GCRY_AC_FLAG_DEALLOC,
			   elements_enc, mpi_encrypted);
  if (err)
    goto out;

  err = _gcry_ac_data_decrypt (handle, 0, key, &mpi_decrypted, data_encrypted);
  if (err)
    goto out;

  err = _gcry_ac_mpi_to_os_alloc (mpi_decrypted, &em, &em_n);
  if (err)
    goto out;

  err = ac_dencode_prepare (handle, key, opts, *scheme, &opts_em);
  if (err)
    goto out;

  _gcry_ac_io_init (&io_em, GCRY_AC_IO_READABLE,
		    GCRY_AC_IO_STRING, em, em_n);

  err = _gcry_ac_data_decode (scheme->scheme_encoding, 0, opts_em,
			      &io_em, io_message);
  if (err)
    goto out;

 out:

  _gcry_ac_data_destroy (data_encrypted);
  gcry_mpi_release (mpi_encrypted);
  gcry_mpi_release (mpi_decrypted);
  free (elements_enc);
  gcry_free (opts_em);
  gcry_free (em);
  gcry_free (c);

  return err;
}
