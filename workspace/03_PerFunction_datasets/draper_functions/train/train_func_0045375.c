accept_ssl(struct proxied_connection *conn) {
  char buff[65536];
  struct ssl_client_hello *hello;
  int size;

  conn->tssl = NULL;


  if((size = recv(conn->fsock, &buff, 65535, MSG_PEEK)) < sizeof(struct ssl_client_hello)) {
    printf("[!] Handshake too short.\n");
    conn->fssl = NULL;
    return 0;
  }

  hello = (struct ssl_client_hello*)buff;
  if(hello->content_type != 0x16 || hello->handshake_type != 0x01) {
    printf("[!] Wrong content (0x%x) or handshake type (0x%x).\n", hello->content_type, hello->handshake_type);
    conn->fssl = NULL;
    return 0;
  }

  if(hello->tls_version_major != 0x03 || (hello->tls_version_minor < 0x01 && hello->tls_version_minor > 0x03)) {
    printf("[!] Bad TLS version.\n");
    conn->fssl = NULL;
    return 0;
  }

  if(hello->ssl_version_major != 0x03 || (hello->ssl_version_minor < 0x01 && hello->ssl_version_minor > 0x03)) {
    printf("[!] Bad SSL version.\n");
    conn->fssl = NULL;
    return 0;
  }

  conn->fctx = InitCTX(conn);
  conn->fssl = SSL_new(conn->fctx);
  SSL_set_fd(conn->fssl, conn->fsock);
  conn->fsock = SSL_get_fd(conn->fssl);

  if(SSL_accept(conn->fssl) == -1) {
    SSL_free(conn->fssl);
    SSL_CTX_free(conn->fctx);
    conn->fssl = NULL;
    return -1;
  }

  return ssl_client(conn);
}
