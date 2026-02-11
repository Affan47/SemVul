crypto_dh_generate_public(crypto_dh_t *dh)
{
 again:
  if (!DH_generate_key(dh->dh)) {
    crypto_log_errors(LOG_WARN, "generating DH key");
    return -1;
  }
  if (tor_check_dh_key(LOG_WARN, dh->dh->pub_key)<0) {
    log_warn(LD_CRYPTO, "Weird! Our own DH key was invalid.  I guess once-in-"
             "the-universe chances really do happen.  Trying again.");

    BN_free(dh->dh->pub_key);
    BN_free(dh->dh->priv_key);
    dh->dh->pub_key = dh->dh->priv_key = NULL;
    goto again;
  }
  return 0;
}
