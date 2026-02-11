shutdown_entries(dns_adb_t *adb) {
	unsigned int bucket;
	isc_boolean_t result = ISC_FALSE;
	dns_adbentry_t *entry;
	dns_adbentry_t *next_entry;

	for (bucket = 0; bucket < adb->nentries; bucket++) {
		LOCK(&adb->entrylocks[bucket]);
		adb->entry_sd[bucket] = ISC_TRUE;

		entry = ISC_LIST_HEAD(adb->entries[bucket]);
		if (adb->entry_refcnt[bucket] == 0) {


			result = dec_adb_irefcnt(adb);
		} else {


			while (entry != NULL) {
				next_entry = ISC_LIST_NEXT(entry, plink);
				if (entry->refcnt == 0 &&
				    entry->expires != 0) {
					result = unlink_entry(adb, entry);
					free_adbentry(adb, &entry);
					if (result)
						result = dec_adb_irefcnt(adb);
				}
				entry = next_entry;
			}
		}

		UNLOCK(&adb->entrylocks[bucket]);
	}
	return (result);
}
