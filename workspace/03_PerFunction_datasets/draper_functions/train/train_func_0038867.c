_gcry_ac_data_verify_scheme (gcry_ac_handle_t handle,
			     gcry_ac_scheme_t scheme_id,
			     unsigned int flags, void *opts,
			     gcry_ac_key_t key,
			     gcry_ac_io_t *io_message,
			     gcry_ac_io_t *io_signature)
{
  gcry_ac_io_t io_em;
  gcry_error_t err;
  gcry_ac_data_t data_signed;
  unsigned char *em;
  size_t em_n;
  void *opts_em;
  gcry_mpi_t mpi_signature;
  gcry_mpi_t mpi_data;
  ac_scheme_t *scheme;
  char *elements_sig;
  size_t elements_sig_n;
  unsigned char *s;
  size_t s_n;

  (void)flags;

  if (fips_mode ())
    return gpg_error (GPG_ERR_NOT_SUPPORTED);

  mpi_signature = NULL;
  elements_sig = NULL;
  data_signed = NULL;
  mpi_data = NULL;
  opts_em = NULL;
  em = NULL;
  s = NULL;

  if (key->type != GCRY_AC_KEY_PUBLIC)
    {
      err = gcry_error (GPG_ERR_WRONG_KEY_USAGE);
      goto out;
    }

  scheme = ac_scheme_get (scheme_id);
  if (! scheme)
    {
      err = gcry_error (GPG_ERR_NO_SIGNATURE_SCHEME);
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

  mpi_data = gcry_mpi_new (0);
  _gcry_ac_os_to_mpi (mpi_data, em, em_n);

  err = _gcry_ac_io_read_all (io_signature, &s, &s_n);
  if (err)
    goto out;

  mpi_signature = gcry_mpi_new (0);
  _gcry_ac_os_to_mpi (mpi_signature, s, s_n);

  err = _gcry_pk_get_elements (handle->algorithm, NULL, &elements_sig);
  if (err)
    goto out;

  elements_sig_n = strlen (elements_sig);
  if (elements_sig_n != 1)
    {

      err = gcry_error (GPG_ERR_CONFLICT);
      goto out;
    }

  err = _gcry_ac_data_new (&data_signed);
  if (err)
    goto out;

  err = _gcry_ac_data_set (data_signed, GCRY_AC_FLAG_COPY | GCRY_AC_FLAG_DEALLOC,
			   elements_sig, mpi_signature);
  if (err)
    goto out;

  gcry_mpi_release (mpi_signature);
  mpi_signature = NULL;

  err = _gcry_ac_data_verify (handle, key, mpi_data, data_signed);

 out:

  _gcry_ac_data_destroy (data_signed);
  gcry_mpi_release (mpi_signature);
  gcry_mpi_release (mpi_data);
  free (elements_sig);
  gcry_free (opts_em);
  gcry_free (em);
  gcry_free (s);

  return err;
}
