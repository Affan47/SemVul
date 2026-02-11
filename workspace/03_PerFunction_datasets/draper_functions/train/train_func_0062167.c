qos_decrypt(request_rec *r, qos_srv_config* sconf, unsigned char **ret_buf, const char *value) {
  EVP_CIPHER_CTX cipher_ctx;

  char *dec = (char *)apr_pcalloc(r->pool, 1 + apr_base64_decode_len(value));
  int dec_len = apr_base64_decode(dec, value);
  *ret_buf = NULL;
  if(dec_len == 0) {
    return 0;
  } else {

    int len = 0;
    int buf_len = 0;
    unsigned char *buf = apr_pcalloc(r->pool, dec_len);
    EVP_CIPHER_CTX_init(&cipher_ctx);
    EVP_DecryptInit(&cipher_ctx, EVP_des_ede3_cbc(), sconf->key, NULL);
    if(!EVP_DecryptUpdate(&cipher_ctx, (unsigned char *)&buf[buf_len], &len,
                          (const unsigned char *)dec, dec_len)) {
      goto failed;
    }
    buf_len+=len;
    if(!EVP_DecryptFinal(&cipher_ctx, (unsigned char *)&buf[buf_len], &len)) {
      goto failed;
    }
    buf_len+=len;
    EVP_CIPHER_CTX_cleanup(&cipher_ctx);
    *ret_buf = buf;
    return buf_len;
  }
 failed:
  EVP_CIPHER_CTX_cleanup(&cipher_ctx);
  return 0;
}
