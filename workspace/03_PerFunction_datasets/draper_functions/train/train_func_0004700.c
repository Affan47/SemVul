dst__openssl_destroy() {


	if (rm != NULL) {
#if OPENSSL_VERSION_NUMBER >= 0x00907000L
		RAND_cleanup();
#endif
		mem_free(rm);
		rm = NULL;
	}
#if (OPENSSL_VERSION_NUMBER >= 0x00907000L)
	CONF_modules_free();
#endif
	OBJ_cleanup();
	EVP_cleanup();
#if defined(USE_ENGINE)
	if (e != NULL)
		ENGINE_free(e);
	e = NULL;
#if defined(USE_ENGINE) && OPENSSL_VERSION_NUMBER >= 0x00907000L
	ENGINE_cleanup();
#endif
#endif
#if (OPENSSL_VERSION_NUMBER >= 0x00907000L)
	CRYPTO_cleanup_all_ex_data();
#endif
	ERR_clear_error();
	ERR_remove_state(0);
	ERR_free_strings();

#ifdef  DNS_CRYPTO_LEAKS
	CRYPTO_mem_leaks_fp(stderr);
#endif

	if (locks != NULL) {
		CRYPTO_set_locking_callback(NULL);
		DESTROYMUTEXBLOCK(locks, nlocks);
		mem_free(locks);
		locks = NULL;
	}
}
