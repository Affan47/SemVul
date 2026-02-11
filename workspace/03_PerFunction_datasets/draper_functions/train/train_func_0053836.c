new_tls_connection(TLS_CONTEXT *ctx, int fd)
{
   BIO *bio;


   bio = BIO_new(BIO_s_socket());
   if (!bio) {

      openssl_post_errors(M_FATAL, _("Error creating file descriptor-based BIO"));
      return NULL;
   }
   BIO_set_fd(bio, fd, BIO_NOCLOSE);


   TLS_CONNECTION *tls = (TLS_CONNECTION *)malloc(sizeof(TLS_CONNECTION));


   if ((tls->openssl = SSL_new(ctx->openssl)) == NULL) {

      openssl_post_errors(M_FATAL, _("Error creating new SSL object"));
      goto err;
   }

   SSL_set_bio(tls->openssl, bio, bio);


   SSL_set_mode(tls->openssl, SSL_MODE_ENABLE_PARTIAL_WRITE|SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);

   return tls;

err:

   BIO_free(bio);
   SSL_free(tls->openssl);
   free(tls);
   return NULL;
}
