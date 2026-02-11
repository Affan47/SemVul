mailstream_ssl_get_certificate(mailstream *stream, unsigned char **cert_DER)
{
#ifdef USE_SSL
  struct mailstream_ssl_data *data = NULL;
  ssize_t len = 0;
#ifndef USE_GNUTLS
  SSL *ssl_conn = NULL;
  X509 *cert = NULL;
#else
  gnutls_session session = NULL;
  const gnutls_datum *raw_cert_list;
  unsigned int raw_cert_list_length;
  gnutls_x509_crt cert = NULL;
  char output[10*1024];
  size_t cert_size;
#endif

  if (cert_DER == NULL || stream == NULL || stream->low == NULL)
    return -1;

  data = stream->low->data;
  if (data == NULL)
    return -1;

#ifndef USE_GNUTLS
  ssl_conn = data->ssl_conn;
  if (ssl_conn == NULL)
    return -1;

  cert = SSL_get_peer_certificate(ssl_conn);
  if (cert == NULL)
    return -1;

  *cert_DER = NULL;
  len = (ssize_t) i2d_X509(cert, cert_DER);

	X509_free(cert);

  return len;
#else
  session = data->session;
  raw_cert_list = gnutls_certificate_get_peers(session, &raw_cert_list_length);

  if (raw_cert_list
  && gnutls_certificate_type_get(session) == GNUTLS_CRT_X509
  &&  gnutls_x509_crt_init(&cert) >= 0
  &&  gnutls_x509_crt_import(cert, &raw_cert_list[0], GNUTLS_X509_FMT_DER) >= 0) {
    cert_size = sizeof(output);
    if (gnutls_x509_crt_export(cert, GNUTLS_X509_FMT_DER, output, &cert_size) < 0)
      return -1;

    *cert_DER = malloc (cert_size + 1);
    if (*cert_DER == NULL)
      return -1;

    memcpy (*cert_DER, output, cert_size);
    len = (ssize_t)cert_size;
    gnutls_x509_crt_deinit(cert);

    return len;
  }
#endif
#endif
  return -1;
}
