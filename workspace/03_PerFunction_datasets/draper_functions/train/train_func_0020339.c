zone_signwithkey(dns_zone_t *zone, dns_secalg_t algorithm, isc_uint16_t keyid,
		 isc_boolean_t delete)
{
	dns_signing_t *signing;
	dns_signing_t *current;
	isc_result_t result = ISC_R_SUCCESS;
	isc_time_t now;
	dns_db_t *db = NULL;

	signing = isc_mem_get(zone->mctx, sizeof *signing);
	if (signing == NULL)
		return (ISC_R_NOMEMORY);

	signing->magic = 0;
	signing->db  = NULL;
	signing->dbiterator = NULL;
	signing->algorithm = algorithm;
	signing->keyid = keyid;
	signing->delete = delete;
	signing->done = ISC_FALSE;

	TIME_NOW(&now);

	ZONEDB_LOCK(&zone->dblock, isc_rwlocktype_read);
	if (zone->db != NULL)
		dns_db_attach(zone->db, &db);
	ZONEDB_UNLOCK(&zone->dblock, isc_rwlocktype_read);

	if (db == NULL) {
		result = ISC_R_NOTFOUND;
		goto cleanup;
	}

	dns_db_attach(db, &signing->db);

	for (current = ISC_LIST_HEAD(zone->signing);
	     current != NULL;
	     current = ISC_LIST_NEXT(current, link)) {
		if (current->db == signing->db &&
		    current->algorithm == signing->algorithm &&
		    current->keyid == signing->keyid) {
			if (current->delete != signing->delete)
				current->done = ISC_TRUE;
			else
				goto cleanup;
		}
	}

	result = dns_db_createiterator(signing->db, 0,
				       &signing->dbiterator);

	if (result == ISC_R_SUCCESS)
		result = dns_dbiterator_first(signing->dbiterator);
	if (result == ISC_R_SUCCESS) {
		dns_dbiterator_pause(signing->dbiterator);
		ISC_LIST_INITANDAPPEND(zone->signing, signing, link);
		signing = NULL;
		if (isc_time_isepoch(&zone->signingtime)) {
			zone->signingtime = now;
			if (zone->task != NULL)
				zone_settimer(zone, &now);
		}
	}

 cleanup:
	if (signing != NULL) {
		if (signing->db != NULL)
			dns_db_detach(&signing->db);
		if (signing->dbiterator != NULL)
			dns_dbiterator_destroy(&signing->dbiterator);
		isc_mem_put(zone->mctx, signing, sizeof *signing);
	}
	if (db != NULL)
		dns_db_detach(&db);
	return (result);
}
