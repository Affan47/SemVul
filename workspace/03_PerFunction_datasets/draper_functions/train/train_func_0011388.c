dns_name_settotextfilter(dns_name_totextfilter_t proc) {
#ifdef ISC_PLATFORM_USETHREADS
	isc_result_t result;
	dns_name_totextfilter_t *mem;
	int res;

	result = totext_filter_proc_key_init();
	if (result != ISC_R_SUCCESS)
		return (result);


	mem = isc_thread_key_getspecific(totext_filter_proc_key);
	if (mem != NULL && proc != NULL) {
		*mem = proc;
		return (ISC_R_SUCCESS);
	}
	if (proc == NULL) {
		isc_mem_put(thread_key_mctx, mem, sizeof(*mem));
		res = isc_thread_key_setspecific(totext_filter_proc_key, NULL);
		if (res != 0)
			result = ISC_R_UNEXPECTED;
		return (result);
	}

	mem = isc_mem_get(thread_key_mctx, sizeof(*mem));
	if (mem == NULL)
		return (ISC_R_NOMEMORY);
	*mem = proc;
	if (isc_thread_key_setspecific(totext_filter_proc_key, mem) != 0) {
		isc_mem_put(thread_key_mctx, mem, sizeof(*mem));
		result = ISC_R_UNEXPECTED;
	}
	return (result);
#else
	totext_filter_proc = proc;
	return (ISC_R_SUCCESS);
#endif
}
