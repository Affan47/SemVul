ac_data_dencode (gcry_ac_em_t method, dencode_action_t action,
		 unsigned int flags, void *options,
		 gcry_ac_io_t *ac_io_read,
		 gcry_ac_io_t *ac_io_write)
{
  struct
  {
    gcry_ac_em_t method;
    gcry_ac_em_dencode_t encode;
    gcry_ac_em_dencode_t decode;
  } methods[] =
    {
      { GCRY_AC_EME_PKCS_V1_5,
	eme_pkcs_v1_5_encode, eme_pkcs_v1_5_decode },
      { GCRY_AC_EMSA_PKCS_V1_5,
	emsa_pkcs_v1_5_encode, NULL },
    };
  size_t methods_n;
  gcry_error_t err;
  unsigned int i;

  methods_n = sizeof (methods) / sizeof (*methods);

  for (i = 0; i < methods_n; i++)
    if (methods[i].method == method)
      break;
  if (i == methods_n)
    {
      err = gcry_error (GPG_ERR_NOT_FOUND);
      goto out;
    }

  err = 0;
  switch (action)
    {
    case DATA_ENCODE:
      if (methods[i].encode)

	err = (*methods[i].encode) (flags, options, ac_io_read, ac_io_write);
      break;

    case DATA_DECODE:
      if (methods[i].decode)

	err = (*methods[i].decode) (flags, options, ac_io_read, ac_io_write);
      break;

    default:
      err = gcry_error (GPG_ERR_INV_ARG);
      break;
    }

 out:

  return err;
}
