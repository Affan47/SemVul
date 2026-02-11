query_iscachevalid(dns_zone_t *zone, dns_db_t *db, dns_db_t *db0,
		   dns_dbversion_t *version)
{
	isc_result_t result = ISC_R_SUCCESS;
	dns_dbversion_t *version_current = NULL;
	dns_db_t *db_current = db0;

	if (db_current == NULL) {
		result = dns_zone_getdb(zone, &db_current);
		if (result != ISC_R_SUCCESS)
			return (result);
	}
	dns_db_currentversion(db_current, &version_current);
	if (db_current != db || version_current != version) {
		result = ISC_R_FAILURE;
		goto cleanup;
	}

 cleanup:
	dns_db_closeversion(db_current, &version_current, ISC_FALSE);
	if (db0 == NULL && db_current != NULL)
		dns_db_detach(&db_current);

	return (result);
}
