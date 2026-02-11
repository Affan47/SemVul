tls_start_clienttls(struct imclient *imclient,
			unsigned *layer, char **authid, int fd)
{
    int     sts;
    SSL_SESSION *session;
    const SSL_CIPHER *cipher;
    X509   *peer;
    int tls_cipher_usebits = 0;
    int tls_cipher_algbits = 0;
    char *tls_peer_CN = "";
    char *tls_issuer_CN = NULL;

    if (imclient->tls_conn == NULL) {
	imclient->tls_conn = (SSL *) SSL_new(imclient->tls_ctx);
    }
    if (imclient->tls_conn == NULL) {
	printf("Could not allocate 'con' with SSL_new()\n");
	return -1;
    }
    SSL_clear(imclient->tls_conn);

    if (!SSL_set_fd(imclient->tls_conn, fd)) {
      printf("SSL_set_fd failed\n");
      return -1;
    }


    SSL_set_connect_state(imclient->tls_conn);


    if ((sts = SSL_connect(imclient->tls_conn)) <= 0) {
	printf("[ SSL_connect error %d ]\n", sts);
	session = SSL_get_session(imclient->tls_conn);
	if (session) {
	    SSL_CTX_remove_session(imclient->tls_ctx, session);
	    printf("[ SSL session removed ]\n");
	}
	if (imclient->tls_conn!=NULL)
	    SSL_free(imclient->tls_conn);
	imclient->tls_conn = NULL;
	return -1;
    }


    peer = SSL_get_peer_certificate(imclient->tls_conn);
    if (peer != NULL) {
	X509_NAME_get_text_by_NID(X509_get_subject_name(peer),
			  NID_commonName, peer_CN, CCERT_BUFSIZ);
	tls_peer_CN = peer_CN;
	X509_NAME_get_text_by_NID(X509_get_issuer_name(peer),
			  NID_commonName, issuer_CN, CCERT_BUFSIZ);


	tls_issuer_CN = issuer_CN;

    }
    cipher = SSL_get_current_cipher(imclient->tls_conn);
    tls_cipher_usebits = SSL_CIPHER_get_bits(cipher,
						 &tls_cipher_algbits);

    if (layer!=NULL)
      *layer = tls_cipher_usebits;

    if (authid!=NULL)
      *authid = tls_peer_CN;


    return 0;
}
