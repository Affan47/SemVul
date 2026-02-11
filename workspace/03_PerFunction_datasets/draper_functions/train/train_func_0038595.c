listener_startclients(ns_lwreslistener_t *listener) {
	ns_lwdclientmgr_t *cm;
	unsigned int i;
	isc_result_t result;


	result = ISC_R_SUCCESS;
	for (i = 0; i < NTASKS && result == ISC_R_SUCCESS; i++)
		result = ns_lwdclientmgr_create(listener, NRECVS,
						ns_g_taskmgr);


	if (ISC_LIST_EMPTY(listener->cmgrs))
		return (result);


	LOCK(&listener->lock);
	cm = ISC_LIST_HEAD(listener->cmgrs);
	while (cm != NULL) {
		result = ns_lwdclient_startrecv(cm);
		if (result != ISC_R_SUCCESS)
			isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
				      NS_LOGMODULE_LWRESD, ISC_LOG_ERROR,
				      "could not start lwres "
				      "client handler: %s",
				      isc_result_totext(result));
		cm = ISC_LIST_NEXT(cm, link);
	}
	UNLOCK(&listener->lock);

	return (ISC_R_SUCCESS);
}
