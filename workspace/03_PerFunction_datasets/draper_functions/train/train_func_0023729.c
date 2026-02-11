dns_adb_shutdown(dns_adb_t *adb) {
	isc_boolean_t need_check_exit;


	LOCK(&adb->lock);

	if (!adb->shutting_down) {
		adb->shutting_down = ISC_TRUE;
		isc_mem_setwater(adb->mctx, water, adb, 0, 0);
		need_check_exit = shutdown_names(adb);
		if (!need_check_exit)
			need_check_exit = shutdown_entries(adb);
		if (need_check_exit)
			check_exit(adb);
	}

	UNLOCK(&adb->lock);
}
