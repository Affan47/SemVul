violate_locking_hierarchy(isc_mutex_t *have, isc_mutex_t *want) {
	if (isc_mutex_trylock(want) != ISC_R_SUCCESS) {
		UNLOCK(have);
		LOCK(want);
		LOCK(have);
	}
}
