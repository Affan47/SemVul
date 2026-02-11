crypto_pk_private_hybrid_decrypt(crypto_pk_t *env,
                                 char *to,
                                 size_t tolen,
                                 const char *from,
                                 size_t fromlen,
                                 int padding, int warnOnFailure)
{
  int outlen, r;
  size_t pkeylen;
  crypto_cipher_t *cipher = NULL;
  char *buf = NULL;

  tor_assert(fromlen < SIZE_T_CEILING);
  pkeylen = crypto_pk_keysize(env);

  if (fromlen <= pkeylen) {
    return crypto_pk_private_decrypt(env,to,tolen,from,fromlen,padding,
                                     warnOnFailure);
  }

  buf = tor_malloc(pkeylen);
  outlen = crypto_pk_private_decrypt(env,buf,pkeylen,from,pkeylen,padding,
                                     warnOnFailure);
  if (outlen<0) {
    log_fn(warnOnFailure?LOG_WARN:LOG_DEBUG, LD_CRYPTO,
           "Error decrypting public-key data");
    goto err;
  }
  if (outlen < CIPHER_KEY_LEN) {
    log_fn(warnOnFailure?LOG_WARN:LOG_INFO, LD_CRYPTO,
           "No room for a symmetric key");
    goto err;
  }
  cipher = crypto_create_init_cipher(buf, 0);
  if (!cipher) {
    goto err;
  }
  memcpy(to,buf+CIPHER_KEY_LEN,outlen-CIPHER_KEY_LEN);
  outlen -= CIPHER_KEY_LEN;
  tor_assert(tolen - outlen >= fromlen - pkeylen);
  r = crypto_cipher_decrypt(cipher, to+outlen, from+pkeylen, fromlen-pkeylen);
  if (r<0)
    goto err;
  memset(buf,0,pkeylen);
  tor_free(buf);
  crypto_cipher_free(cipher);
  tor_assert(outlen + fromlen < INT_MAX);
  return (int)(outlen + (fromlen-pkeylen));
 err:
  memset(buf,0,pkeylen);
  tor_free(buf);
  if (cipher) crypto_cipher_free(cipher);
  return -1;
}
