print_crl_info (gnutls_x509_crl_t crl, FILE * out)
{
  gnutls_datum_t cinfo;
  int ret;
  size_t size;

  ret = gnutls_x509_crl_print (crl, GNUTLS_CRT_PRINT_FULL, &cinfo);
  if (ret < 0)
    error (EXIT_FAILURE, 0, "crl_print: %s", gnutls_strerror (ret));

  fprintf (out, "%s\n", cinfo.data);

  gnutls_free (cinfo.data);

  size = buffer_size;
  ret = gnutls_x509_crl_export (crl, GNUTLS_X509_FMT_PEM, buffer, &size);
  if (ret < 0)
    error (EXIT_FAILURE, 0, "crl_export: %s", gnutls_strerror (ret));

  fwrite (buffer, 1, size, outfile);
}
