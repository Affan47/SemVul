crypto_dh_compute_secret(int severity, crypto_dh_t *dh,
                         const char *pubkey, size_t pubkey_len,
                         char *secret_out, size_t secret_bytes_out)
{
  char *secret_tmp = NULL;
  BIGNUM *pubkey_bn = NULL;
  size_t secret_len=0, secret_tmp_len=0;
  int result=0;
  tor_assert(dh);
  tor_assert(secret_bytes_out/DIGEST_LEN <= 255);
  tor_assert(pubkey_len < INT_MAX);

  if (!(pubkey_bn = BN_bin2bn((const unsigned char*)pubkey,
                              (int)pubkey_len, NULL)))
    goto error;
  if (tor_check_dh_key(severity, pubkey_bn)<0) {

    log_fn(severity, LD_CRYPTO,"Rejected invalid g^x");
    goto error;
  }
  secret_tmp_len = crypto_dh_get_bytes(dh);
  secret_tmp = tor_malloc(secret_tmp_len);
  result = DH_compute_key((unsigned char*)secret_tmp, pubkey_bn, dh->dh);
  if (result < 0) {
    log_warn(LD_CRYPTO,"DH_compute_key() failed.");
    goto error;
  }
  secret_len = result;
  if (crypto_expand_key_material(secret_tmp, secret_len,
                                 secret_out, secret_bytes_out)<0)
    goto error;
  secret_len = secret_bytes_out;

  goto done;
 error:
  result = -1;
 done:
  crypto_log_errors(LOG_WARN, "completing DH handshake");
  if (pubkey_bn)
    BN_free(pubkey_bn);
  if (secret_tmp) {
    memset(secret_tmp, 0, secret_tmp_len);
    tor_free(secret_tmp);
  }
  if (result < 0)
    return result;
  else
    return secret_len;
}
