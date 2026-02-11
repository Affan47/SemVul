gnutls_certificate_set_x509_simple_pkcs12_file
  (gnutls_certificate_credentials_t res, const char *pkcs12file,
   gnutls_x509_crt_fmt_t type, const char *password)
{
  gnutls_datum_t p12blob;
  size_t size;
  int ret;

  p12blob.data = read_binary_file (pkcs12file, &size);
  p12blob.size = (unsigned int) size;
  if (p12blob.data == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_FILE_ERROR;
    }

  ret =
    gnutls_certificate_set_x509_simple_pkcs12_mem (res, &p12blob, type,
                                                   password);
  free (p12blob.data);

  return ret;
}
