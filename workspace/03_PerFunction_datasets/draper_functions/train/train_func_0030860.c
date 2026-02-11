inf_cert_util_get_fingerprint(gnutls_x509_crt_t cert,
                              gnutls_digest_algorithm_t algo)
{
  int ret;
  size_t size;
  guchar* value;
  gchar* formatted;

  size = 0;
  ret = gnutls_x509_crt_get_fingerprint(cert, algo, NULL, &size);
  if(ret != GNUTLS_E_SHORT_MEMORY_BUFFER) return NULL;

  value = g_malloc(size);
  ret = gnutls_x509_crt_get_fingerprint(cert, algo, value, &size);
  if(ret != GNUTLS_E_SUCCESS) return NULL;

  formatted = inf_cert_util_format_hexadecimal(value, size);
  g_free(value);

  return formatted;
}
