cdk_sk_release (cdk_seckey_t sk)
{
  size_t nskey;

  if (!sk)
    return;

  nskey = cdk_pk_get_nskey (sk->pubkey_algo);
  _cdk_free_mpibuf (nskey, sk->mpi);
  cdk_free (sk->encdata);
  sk->encdata = NULL;
  cdk_pk_release (sk->pk);
  sk->pk = NULL;
  cdk_s2k_free (sk->protect.s2k);
  sk->protect.s2k = NULL;
  cdk_free (sk);
}
