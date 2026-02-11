sge_done_shared_ssl_lib(void)
{
   int ret;

   DENTER(TOP_LAYER, "sge_done_shared_ssl_lib");
#ifdef LOAD_OPENSSL
   if (shared_ssl_lib != NULL) {
      shared_ssl_func__X509_free = NULL;
      shared_ssl_func__EVP_PKEY_free = NULL;
      shared_ssl_func__ERR_print_errors_fp = NULL;
      shared_ssl_func__EVP_PKEY_size = NULL;
      shared_ssl_func__EVP_rc4 = NULL;
      shared_ssl_func__EVP_OpenInit = NULL;
      shared_ssl_func__EVP_DecryptUpdate = NULL;
      shared_ssl_func__EVP_EncryptUpdate = NULL;
      shared_ssl_func__EVP_SealFinal = NULL;
      shared_ssl_func__EVP_SealInit = NULL;
      shared_ssl_func__EVP_OpenFinal = NULL;
      shared_ssl_func__EVP_read_pw_string = NULL;
      shared_ssl_func__ERR_load_crypto_strings = NULL;
      shared_ssl_func__X509_get_pubkey = NULL;
      shared_ssl_func__PEM_ASN1_read = NULL;
      shared_ssl_func__d2i_AutoPrivateKey = NULL;
      shared_ssl_func__d2i_X509 = NULL;
      shared_ssl_func__RAND_load_file = NULL;
      dlclose(shared_ssl_lib);
      shared_ssl_lib = NULL;
      ret = 0;
   } else {
      ret = 1;
   }
#else
   ret = 0;
#endif
   DEXIT;
   return ret;
}
