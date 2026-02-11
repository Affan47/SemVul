_gcry_ac_data_verify (gcry_ac_handle_t handle,
		      gcry_ac_key_t key,
		      gcry_mpi_t data,
		      gcry_ac_data_t data_signature)
{
  gcry_sexp_t sexp_signature;
  gcry_ac_data_t data_value;
  gcry_sexp_t sexp_data;
  gcry_sexp_t sexp_key;
  gcry_error_t err;

  if (fips_mode ())
    return gpg_error (GPG_ERR_NOT_SUPPORTED);

  sexp_signature = NULL;
  data_value = NULL;
  sexp_data = NULL;
  sexp_key = NULL;

  err = ac_data_construct ("public-key", 0, 0,
			   handle->algorithm_name, key->data, &sexp_key);
  if (err)
    goto out;

  if (key->type != GCRY_AC_KEY_PUBLIC)
    {
      err = gcry_error (GPG_ERR_WRONG_KEY_USAGE);
      goto out;
    }


  err = ac_data_construct ("sig-val", 1, 0, handle->algorithm_name,
			   data_signature, &sexp_signature);
  if (err)
    goto out;

  err = _gcry_ac_data_new (&data_value);
  if (err)
    goto out;

  err = _gcry_ac_data_set (data_value, 0, "value", data);
  if (err)
    goto out;


  err = ac_data_construct ("data", 1, 0, NULL, data_value, &sexp_data);
  if (err)
    goto out;


  err = gcry_pk_verify (sexp_signature, sexp_data, sexp_key);

 out:

  gcry_sexp_release (sexp_signature);
  gcry_sexp_release (sexp_data);
  gcry_sexp_release (sexp_key);
  _gcry_ac_data_destroy (data_value);

  return gcry_error (err);
}
