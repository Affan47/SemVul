_cdk_copy_seckey (cdk_pkt_seckey_t * dst, cdk_pkt_seckey_t src)
{
  cdk_pkt_seckey_t k;
  int i;

  if (!dst || !src)
    return CDK_Inv_Value;

  *dst = NULL;
  k = cdk_calloc (1, sizeof *k);
  if (!k)
    return CDK_Out_Of_Core;
  memcpy (k, src, sizeof *k);
  _cdk_copy_pubkey (&k->pk, src->pk);

  if (src->encdata)
    {
      k->encdata = cdk_calloc (1, src->enclen + 1);
      if (!k->encdata)
        return CDK_Out_Of_Core;
      memcpy (k->encdata, src->encdata, src->enclen);
    }

  _cdk_s2k_copy (&k->protect.s2k, src->protect.s2k);
  for (i = 0; i < cdk_pk_get_nskey (src->pubkey_algo); i++)
    {
      k->mpi[i] = _gnutls_mpi_copy (src->mpi[i]);
    }

  *dst = k;
  return 0;
}
