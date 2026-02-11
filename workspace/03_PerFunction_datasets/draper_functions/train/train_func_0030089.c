flushandsync(FILE *f, isc_result_t result, const char *temp) {
	isc_boolean_t logit = ISC_TF(result == ISC_R_SUCCESS);

	if (result == ISC_R_SUCCESS)
		result = isc_stdio_flush(f);
	if (result != ISC_R_SUCCESS && logit) {
		if (temp != NULL)
			isc_log_write(dns_lctx, ISC_LOGCATEGORY_GENERAL,
				      DNS_LOGMODULE_MASTERDUMP, ISC_LOG_ERROR,
				      "dumping to master file: %s: flush: %s",
				      temp, isc_result_totext(result));
		else
			isc_log_write(dns_lctx, ISC_LOGCATEGORY_GENERAL,
				      DNS_LOGMODULE_MASTERDUMP, ISC_LOG_ERROR,
				      "dumping to stream: flush: %s",
				      isc_result_totext(result));
		logit = ISC_FALSE;
	}

	if (result == ISC_R_SUCCESS)
		result = isc_stdio_sync(f);
	if (result != ISC_R_SUCCESS && logit) {
		if (temp != NULL)
			isc_log_write(dns_lctx, ISC_LOGCATEGORY_GENERAL,
				      DNS_LOGMODULE_MASTERDUMP, ISC_LOG_ERROR,
				      "dumping to master file: %s: fsync: %s",
				      temp, isc_result_totext(result));
		else
			isc_log_write(dns_lctx, ISC_LOGCATEGORY_GENERAL,
				      DNS_LOGMODULE_MASTERDUMP, ISC_LOG_ERROR,
				      "dumping to stream: fsync: %s",
				      isc_result_totext(result));
	}
	return (result);
}
