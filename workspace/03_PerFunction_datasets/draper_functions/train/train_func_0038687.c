license_job_test(struct job_record *job_ptr, time_t when)
{
	ListIterator iter;
	licenses_t *license_entry, *match;
	int rc = SLURM_SUCCESS, resv_licenses;

	if (!job_ptr->license_list)
		return rc;

	slurm_mutex_lock(&license_mutex);
	iter = list_iterator_create(job_ptr->license_list);
	while ((license_entry = (licenses_t *) list_next(iter))) {
		match = list_find_first(license_list, _license_find_rec,
			license_entry->name);
		if (!match) {
			error("could not find license %s for job %u",
			      license_entry->name, job_ptr->job_id);
			rc = SLURM_ERROR;
			break;
		} else if (license_entry->total > match->total) {
			info("job %u wants more %s licenses than configured",
			     job_ptr->job_id, match->name);
			rc = SLURM_ERROR;
			break;
		} else if ((license_entry->total + match->used) >
			   match->total) {
			rc = EAGAIN;
			break;
		} else {
			resv_licenses = job_test_lic_resv(job_ptr,
							  license_entry->name,
							  when);
			if ((license_entry->total + match->used +
			     resv_licenses) > match->total) {
				rc = EAGAIN;
				break;
			}
		}
	}
	list_iterator_destroy(iter);
	slurm_mutex_unlock(&license_mutex);
	return rc;
}
