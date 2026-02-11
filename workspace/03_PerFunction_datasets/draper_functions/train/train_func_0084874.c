ns_log_setsafechannels(isc_logconfig_t *lcfg) {
	isc_result_t result;
	isc_logdestination_t destination;

	if (! ns_g_logstderr) {
		result = isc_log_createchannel(lcfg, "default_debug",
					       ISC_LOG_TONULL,
					       ISC_LOG_DYNAMIC,
					       NULL, 0);
		if (result != ISC_R_SUCCESS)
			goto cleanup;


		isc_log_setdebuglevel(ns_g_lctx, 0);
	} else {
		isc_log_setdebuglevel(ns_g_lctx, ns_g_debuglevel);
	}

	if (ns_g_logfile != NULL) {
		destination.file.stream = NULL;
		destination.file.name = ns_g_logfile;
		destination.file.versions = ISC_LOG_ROLLNEVER;
		destination.file.maximum_size = 0;
		result = isc_log_createchannel(lcfg, "default_logfile",
					       ISC_LOG_TOFILE,
					       ISC_LOG_DYNAMIC,
					       &destination,
					       ISC_LOG_PRINTTIME|
					       ISC_LOG_PRINTCATEGORY|
					       ISC_LOG_PRINTLEVEL);
		if (result != ISC_R_SUCCESS)
			goto cleanup;
	}

#if ISC_FACILITY != LOG_DAEMON
	destination.facility = ISC_FACILITY;
	result = isc_log_createchannel(lcfg, "default_syslog",
				       ISC_LOG_TOSYSLOG, ISC_LOG_INFO,
				       &destination, 0);
	if (result != ISC_R_SUCCESS)
		goto cleanup;
#endif

	result = ISC_R_SUCCESS;

 cleanup:
	return (result);
}
