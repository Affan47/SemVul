SslFd_set_ssl_general(SslFd* sf, SSL* ssl, int free)
{
  assert(sf != NULL);
  if (sf == NULL) {
    return;
  }
  if ((free) && (sf->ssl)) {
    SSL_free(sf->ssl);
  }
  sf->ssl = ssl;
}
