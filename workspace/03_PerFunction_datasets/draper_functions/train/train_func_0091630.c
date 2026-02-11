cdk_pk_verify (cdk_pubkey_t pk, cdk_pkt_signature_t sig, const byte * md)
{
  gnutls_datum_t s_sig;
  byte *encmd = NULL;
  size_t enclen;
  cdk_error_t rc;
  int ret, algo;
  unsigned int i;
  gnutls_datum_t data;
  gnutls_pk_params_st params;

  if (!pk || !sig || !md)
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }

  if (is_DSA (pk->pubkey_algo))
    algo = GNUTLS_PK_DSA;
  else if (is_RSA (pk->pubkey_algo))
    algo = GNUTLS_PK_RSA;
  else
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }

  rc = sig_to_datum (&s_sig, sig);
  if (rc)
    {
      gnutls_assert ();
      goto leave;
    }

  rc = _cdk_digest_encode_pkcs1 (&encmd, &enclen, pk->pubkey_algo, md,
                                 sig->digest_algo, cdk_pk_get_nbits (pk));
  if (rc)
    {
      gnutls_assert ();
      goto leave;
    }

  data.data = encmd;
  data.size = enclen;

  params.params_nr = cdk_pk_get_npkey (pk->pubkey_algo);
  for (i = 0; i < params.params_nr; i++)
    params.params[i] = pk->mpi[i];
  params.flags = 0;
  ret = _gnutls_pk_verify (algo, &data, &s_sig, &params);

  if (ret < 0)
    {
      gnutls_assert ();
      rc = map_gnutls_error (ret);
      goto leave;
    }

  rc = 0;

leave:
  _gnutls_free_datum (&s_sig);
  cdk_free (encmd);
  return rc;
}
