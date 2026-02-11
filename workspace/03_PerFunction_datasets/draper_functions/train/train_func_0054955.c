cm_check_expiration_is_noteworthy(struct cm_store_entry *entry,
				  int (*get_ttls)(const time_t **,
						  unsigned int *),
				  time_t *last_check)
{
	unsigned int i, n_ttls;
	time_t now, ttl, previous_ttl;
	const time_t *ttls;
	now = cm_time(NULL);

	if (entry->cm_cert_not_after == 0) {
		return -1;
	}

	if (entry->cm_cert_not_before > (now - 60 * 60 )) {
		return -1;
	}

	if (entry->cm_cert_not_after < now) {
		ttl = 0;
	} else {
		ttl = entry->cm_cert_not_after - now;
	}

	if (entry->cm_cert_not_after < *last_check) {
		previous_ttl = 0;
	} else {
		previous_ttl = entry->cm_cert_not_after - *last_check;
	}

	*last_check = now;

	ttls = NULL;
	n_ttls = 0;
	if (((*get_ttls)(&ttls, &n_ttls) != 0) || (n_ttls == 0)) {
		return -1;
	}

	for (i = 0; i < n_ttls; i++) {

		if ((ttl < ttls[i]) && (previous_ttl >= ttls[i])) {
			return 0;
		}

		if ((ttl >= ttls[i]) && (previous_ttl < ttls[i])) {
			return 0;
		}
	}

	if (ttl == 0) {
		return 0;
	}
	return -1;
}
