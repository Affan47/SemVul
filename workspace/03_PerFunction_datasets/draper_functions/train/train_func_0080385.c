crypto_pk_write_key_to_string_impl(crypto_pk_t *env, char **dest,
                                   size_t *len, int is_public)
{
  BUF_MEM *buf;
  BIO *b;
  int r;

  tor_assert(env);
  tor_assert(env->key);
  tor_assert(dest);

  b = BIO_new(BIO_s_mem());
  if (!b)
    return -1;


  if (is_public)
    r = PEM_write_bio_RSAPublicKey(b, env->key);
  else
    r = PEM_write_bio_RSAPrivateKey(b, env->key, NULL,NULL,0,NULL,NULL);

  if (!r) {
    crypto_log_errors(LOG_WARN, "writing RSA key to string");
    BIO_free(b);
    return -1;
  }

  BIO_get_mem_ptr(b, &buf);
  (void)BIO_set_close(b, BIO_NOCLOSE);
  BIO_free(b);

  *dest = tor_malloc(buf->length+1);
  memcpy(*dest, buf->data, buf->length);
  (*dest)[buf->length] = 0;
  *len = buf->length;
  BUF_MEM_free(buf);

  return 0;
}
