toresult(isc_result_t fallback) {
	isc_result_t result = fallback;
	unsigned long err = ERR_get_error();
#ifdef HAVE_OPENSSL_ECDSA
	int lib = ERR_GET_LIB(err);
#endif
	int reason = ERR_GET_REASON(err);

	switch (reason) {


	case ERR_R_MALLOC_FAILURE:
		result = ISC_R_NOMEMORY;
		break;
	default:
#ifdef HAVE_OPENSSL_ECDSA
		if (lib == ERR_R_ECDSA_LIB &&
		    reason == ECDSA_R_RANDOM_NUMBER_GENERATION_FAILED) {
			result = ISC_R_NOENTROPY;
			break;
		}
#endif
		break;
	}

	return (result);
}
