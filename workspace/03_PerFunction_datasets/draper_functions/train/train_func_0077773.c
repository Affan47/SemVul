_get_batch_job_dir_ids(List batch_dirs)
{
	DIR *f_dir;
	struct dirent *dir_ent;
	long long_job_id;
	uint32_t *job_id_ptr;
	char *endptr;

	xassert(slurmctld_conf.state_save_location);
	f_dir = opendir(slurmctld_conf.state_save_location);
	if (!f_dir) {
		error("opendir(%s): %m",
		      slurmctld_conf.state_save_location);
		return;
	}

	while ((dir_ent = readdir(f_dir))) {
		if (strncmp("job.#", dir_ent->d_name, 4))
			continue;
		long_job_id = strtol(&dir_ent->d_name[4], &endptr, 10);
		if ((long_job_id == 0) || (endptr[0] != '\0'))
			continue;
		debug3("found batch directory for job_id %ld", long_job_id);
		job_id_ptr = xmalloc(sizeof(uint32_t));
		*job_id_ptr = long_job_id;
		list_append (batch_dirs, job_id_ptr);
	}

	closedir(f_dir);
}
