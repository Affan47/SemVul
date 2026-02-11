set_ssl_option(struct mg_context *ctx) {
  int i, size;
  const char *pem;


  if ((pem = ctx->config[SSL_CERTIFICATE]) == NULL) {
    return 1;
  }

#if !defined(NO_SSL_DL)
  if (!load_dll(ctx, SSL_LIB, ssl_sw) ||
      !load_dll(ctx, CRYPTO_LIB, crypto_sw)) {
    return 0;
  }
#endif


  SSL_library_init();
  SSL_load_error_strings();

  if ((ctx->client_ssl_ctx = SSL_CTX_new(SSLv23_client_method())) == NULL) {
    cry(fc(ctx), "SSL_CTX_new (client) error: %s", ssl_error());
  }

  if ((ctx->ssl_ctx = SSL_CTX_new(SSLv23_server_method())) == NULL) {
    cry(fc(ctx), "SSL_CTX_new (server) error: %s", ssl_error());
    return 0;
  }


  if (call_user(fc(ctx), MG_INIT_SSL) == NULL &&
      (SSL_CTX_use_certificate_file(ctx->ssl_ctx, pem, SSL_FILETYPE_PEM) == 0 ||
       SSL_CTX_use_PrivateKey_file(ctx->ssl_ctx, pem, SSL_FILETYPE_PEM) == 0)) {
    cry(fc(ctx), "%s: cannot open %s: %s", __func__, pem, ssl_error());
    return 0;
  }

  if (pem != NULL) {
    (void) SSL_CTX_use_certificate_chain_file(ctx->ssl_ctx, pem);
  }


  size = sizeof(pthread_mutex_t) * CRYPTO_num_locks();
  if ((ssl_mutexes = (pthread_mutex_t *) malloc((size_t)size)) == NULL) {
    cry(fc(ctx), "%s: cannot allocate mutexes: %s", __func__, ssl_error());
    return 0;
  }

  for (i = 0; i < CRYPTO_num_locks(); i++) {
    pthread_mutex_init(&ssl_mutexes[i], NULL);
  }

  CRYPTO_set_locking_callback(&ssl_locking_callback);
  CRYPTO_set_id_callback(&ssl_id_callback);

  return 1;
}
