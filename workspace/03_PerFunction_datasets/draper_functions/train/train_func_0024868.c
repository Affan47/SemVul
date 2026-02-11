gnutls_x509_crt_get_verify_algorithm (gnutls_x509_crt_t crt,
                                      const gnutls_datum_t * signature,
                                      gnutls_digest_algorithm_t * hash)
{
  bigint_t issuer_params[MAX_PUBLIC_PARAMS_SIZE];
  int issuer_params_size;
  int ret, i;

  if (crt == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  issuer_params_size = MAX_PUBLIC_PARAMS_SIZE;
  ret = _gnutls_x509_crt_get_mpis (crt, issuer_params, &issuer_params_size);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  ret = _gnutls_x509_verify_algorithm ((gnutls_mac_algorithm_t *) hash,
                                       signature,
                                       gnutls_x509_crt_get_pk_algorithm (crt,
                                                                         NULL),
                                       issuer_params, issuer_params_size);


  for (i = 0; i < issuer_params_size; i++)
    {
      _gnutls_mpi_release (&issuer_params[i]);
    }

  return ret;
}
