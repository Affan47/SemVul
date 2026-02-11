_find_or_create_driver_cap(dbi_driver_t *driver, const char *capname) {
	_capability_t *prevcap = NULL;
	_capability_t *cap = driver->caps;

	while (cap && strcmp(capname, cap->name)) {
		prevcap = cap;
		cap = cap->next;
	}

	if (cap == NULL) {

		cap = malloc(sizeof(_capability_t));
		if (!cap) return NULL;
		cap->name = strdup(capname);
		cap->next = NULL;
		if (driver->caps == NULL) {
		    driver->caps = cap;
		}
		else {
		    prevcap->next = cap;
		}
	}

	return cap;
}
