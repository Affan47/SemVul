print_crq_info (gnutls_x509_crq_t crq, FILE * out)
{
  gnutls_datum_t cinfo;
  int ret;
  size_t size;

  if (info.outcert_format == GNUTLS_X509_FMT_PEM)
    {
      ret = gnutls_x509_crq_print (crq, GNUTLS_CRT_PRINT_FULL, &cinfo);
      if (ret < 0)
        error (EXIT_FAILURE, 0, "crq_print: %s", gnutls_strerror (ret));

      fprintf (out, "%s\n", cinfo.data);

      gnutls_free (cinfo.data);
    }

  size = buffer_size;
  ret = gnutls_x509_crq_export (crq, info.outcert_format, buffer, &size);
  if (ret < 0)
    error (EXIT_FAILURE, 0, "crq_export: %s", gnutls_strerror (ret));

  fwrite (buffer, 1, size, outfile);
}
