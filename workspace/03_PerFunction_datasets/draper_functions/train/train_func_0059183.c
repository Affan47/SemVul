_generate_params (int algo, bigint_t * resarr, unsigned int *resarr_len,
                  int bits)
{
  gnutls_pk_params_st params;
  int ret;
  unsigned int i;

  ret = _gnutls_pk_ops.generate (algo, bits, &params);

  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  if (resarr && resarr_len && *resarr_len >= params.params_nr)
    {
      *resarr_len = params.params_nr;
      for (i = 0; i < params.params_nr; i++)
        resarr[i] = params.params[i];
    }
  else
    {
      gnutls_pk_params_release(&params);
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }
  return 0;
}
