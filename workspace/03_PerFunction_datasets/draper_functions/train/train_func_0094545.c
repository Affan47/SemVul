print_certificate_info (gnutls_x509_crt_t crt, FILE * out, unsigned int all)
{
  gnutls_datum_t cinfo;
  int ret;

  if (all)
    ret = gnutls_x509_crt_print (crt, GNUTLS_CRT_PRINT_FULL, &cinfo);
  else
    ret = gnutls_x509_crt_print (crt, GNUTLS_CRT_PRINT_UNSIGNED_FULL, &cinfo);
  if (ret == 0)
    {
      fprintf (out, "%s\n", cinfo.data);
      gnutls_free (cinfo.data);
    }

  if (out == stderr && batch == 0)
    if (read_yesno ("Is the above information ok? (y/N): ") == 0)
      {
        exit (1);
      }
}
