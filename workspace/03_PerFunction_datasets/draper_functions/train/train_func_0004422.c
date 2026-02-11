init_ssl(void)
{
	SSL_library_init();
	ERR_load_crypto_strings();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
	if (SSLeay() != OPENSSL_VERSION_NUMBER) {
		TT_DECLARE("WARN", ("Version mismatch for openssl: compiled with %lx but running with %lx", (unsigned long)OPENSSL_VERSION_NUMBER, (unsigned long) SSLeay()));
	}
}
