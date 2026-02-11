new_tls_context(const char *ca_certfile, const char *ca_certdir,
                             const char *certfile, const char *keyfile,
                             CRYPTO_PEM_PASSWD_CB *pem_callback,
                             const void *pem_userdata, const char *dhfile,
                             bool verify_peer)
{
   TLS_CONTEXT *ctx;
   BIO *bio;
   DH *dh;

   ctx = (TLS_CONTEXT *)malloc(sizeof(TLS_CONTEXT));


   ctx->openssl = SSL_CTX_new(TLSv1_method());

   if (!ctx->openssl) {
      openssl_post_errors(M_FATAL, _("Error initializing SSL context"));
      goto err;
   }


   if (pem_callback) {
      ctx->pem_callback = pem_callback;
      ctx->pem_userdata = pem_userdata;
   } else {
      ctx->pem_callback = crypto_default_pem_callback;
      ctx->pem_userdata = NULL;
   }
   SSL_CTX_set_default_passwd_cb(ctx->openssl, tls_pem_callback_dispatch);
   SSL_CTX_set_default_passwd_cb_userdata(ctx->openssl, (void *) ctx);


   if (ca_certfile || ca_certdir) {
      if (!SSL_CTX_load_verify_locations(ctx->openssl, ca_certfile, ca_certdir)) {
         openssl_post_errors(M_FATAL, _("Error loading certificate verification stores"));
         goto err;
      }
   } else if (verify_peer) {

      Jmsg0(NULL, M_ERROR, 0, _("Either a certificate file or a directory must be"
                         " specified as a verification store\n"));
      goto err;
   }


   if (certfile) {
      if (!SSL_CTX_use_certificate_chain_file(ctx->openssl, certfile)) {
         openssl_post_errors(M_FATAL, _("Error loading certificate file"));
         goto err;
      }
   }


   if (keyfile) {
      if (!SSL_CTX_use_PrivateKey_file(ctx->openssl, keyfile, SSL_FILETYPE_PEM)) {
         openssl_post_errors(M_FATAL, _("Error loading private key"));
         goto err;
      }
   }


   if (dhfile) {
      if (!(bio = BIO_new_file(dhfile, "r"))) {
         openssl_post_errors(M_FATAL, _("Unable to open DH parameters file"));
         goto err;
      }
      dh = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
      BIO_free(bio);
      if (!dh) {
         openssl_post_errors(M_FATAL, _("Unable to load DH parameters from specified file"));
         goto err;
      }
      if (!SSL_CTX_set_tmp_dh(ctx->openssl, dh)) {
         openssl_post_errors(M_FATAL, _("Failed to set TLS Diffie-Hellman parameters"));
         DH_free(dh);
         goto err;
      }

      SSL_CTX_set_options(ctx->openssl, SSL_OP_SINGLE_DH_USE);
   }

   if (SSL_CTX_set_cipher_list(ctx->openssl, TLS_DEFAULT_CIPHERS) != 1) {
      Jmsg0(NULL, M_ERROR, 0,
             _("Error setting cipher list, no valid ciphers available\n"));
      goto err;
   }


   if (verify_peer) {

      SSL_CTX_set_verify(ctx->openssl,
                         SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
                         openssl_verify_peer);
   }

   return ctx;

err:

   if(ctx->openssl) {
      SSL_CTX_free(ctx->openssl);
   }
   free(ctx);
   return NULL;
}
