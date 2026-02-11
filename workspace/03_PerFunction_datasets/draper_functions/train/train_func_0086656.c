license_update(char *licenses)
{
	ListIterator iter;
	licenses_t *license_entry, *match;
	List new_list;
	bool valid;

	new_list = _build_license_list(licenses, &valid);
	if (!valid)
		fatal("Invalid configured licenses: %s", licenses);

	slurm_mutex_lock(&license_mutex);
	if (!license_list) {
		license_list = new_list;
		slurm_mutex_unlock(&license_mutex);
		return SLURM_SUCCESS;
	}

	iter = list_iterator_create(license_list);
	while ((license_entry = (licenses_t *) list_next(iter))) {
		match = list_find_first(new_list, _license_find_rec,
			license_entry->name);
		if (!match) {
			info("license %s removed with %u in use",
			     license_entry->name, license_entry->used);
		} else {
			match->used = license_entry->used;
			if (match->used > match->total) {
				info("license %s count decreased",
				     match->name);
			}
		}
	}
	list_iterator_destroy(iter);

	list_destroy(license_list);
	license_list = new_list;
	_licenses_print("update_license", license_list, 0);
	slurm_mutex_unlock(&license_mutex);
	return SLURM_SUCCESS;
}
