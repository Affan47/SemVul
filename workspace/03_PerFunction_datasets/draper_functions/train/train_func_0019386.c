cdk_pk_release (cdk_pubkey_t pk)
{
  size_t npkey;

  if (!pk)
    return;

  npkey = cdk_pk_get_npkey (pk->pubkey_algo);
  _cdk_free_userid (pk->uid);
  pk->uid = NULL;
  cdk_free (pk->prefs);
  pk->prefs = NULL;
  _cdk_free_mpibuf (npkey, pk->mpi);
  cdk_free (pk);
}
