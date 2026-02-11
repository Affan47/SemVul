setup_logging(isc_mem_t *mctx, FILE *errout, isc_log_t **logp) {
	isc_logdestination_t destination;
	isc_logconfig_t *logconfig = NULL;
	isc_log_t *log = NULL;

	RUNTIME_CHECK(isc_log_create(mctx, &log, &logconfig) == ISC_R_SUCCESS);
	isc_log_registercategories(log, categories);
	isc_log_setcontext(log);
	dns_log_init(log);
	dns_log_setcontext(log);
	cfg_log_init(log);

	destination.file.stream = errout;
	destination.file.name = NULL;
	destination.file.versions = ISC_LOG_ROLLNEVER;
	destination.file.maximum_size = 0;
	RUNTIME_CHECK(isc_log_createchannel(logconfig, "stderr",
				       ISC_LOG_TOFILEDESC,
				       ISC_LOG_DYNAMIC,
				       &destination, 0) == ISC_R_SUCCESS);
	RUNTIME_CHECK(isc_log_usechannel(logconfig, "stderr",
					 NULL, NULL) == ISC_R_SUCCESS);

	*logp = log;
	return (ISC_R_SUCCESS);
}
