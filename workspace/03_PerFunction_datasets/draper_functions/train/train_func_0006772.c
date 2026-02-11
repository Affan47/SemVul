read_public_key(const char *certfile)
{
   FILE *fp = NULL;
   X509 *x509;
   EVP_PKEY *pkey = NULL;

   DENTER(TOP_LAYER, "read_public_key");
   fp = fopen(certfile, "r");
   if (!fp) {
      DEXIT;
      return NULL;
   }
   x509 = shared_ssl_func__PEM_read_X509(fp, NULL, 0, NULL);
   if (x509 == NULL) {
      shared_ssl_func__ERR_print_errors_fp(stderr);
      DEXIT;
      return NULL;
   }
   FCLOSE (fp);
   pkey = shared_ssl_func__X509_extract_key(x509);
   shared_ssl_func__X509_free(x509);
   if (pkey == NULL) {
      shared_ssl_func__ERR_print_errors_fp(stderr);
   }
FCLOSE_ERROR:
   DEXIT;
   return pkey;
}
