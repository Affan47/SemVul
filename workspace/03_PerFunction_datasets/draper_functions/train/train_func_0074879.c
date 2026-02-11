_job_fini(void *args)
{
	struct job_record *job_ptr = (struct job_record *)args;
	nhc_info_t nhc_info;


	slurmctld_lock_t job_write_lock = {
		NO_LOCK, WRITE_LOCK, WRITE_LOCK, NO_LOCK
	};
	slurmctld_lock_t job_read_lock = {
		NO_LOCK, READ_LOCK, NO_LOCK, NO_LOCK };


	if (!job_ptr) {
		error("_job_fini: no job ptr given, this should never happen");
		return NULL;
	}

	memset(&nhc_info, 0, sizeof(nhc_info_t));
	lock_slurmctld(job_read_lock);
	nhc_info.jobid = job_ptr->job_id;
	nhc_info.nodelist = xstrdup(job_ptr->nodes);
	nhc_info.exit_code = 1;
	unlock_slurmctld(job_read_lock);


	_run_nhc(&nhc_info);

	xfree(nhc_info.nodelist);

	lock_slurmctld(job_write_lock);
	if (job_ptr->magic == JOB_MAGIC) {
		select_jobinfo_t *jobinfo = NULL;
		other_job_fini(job_ptr);

		jobinfo = job_ptr->select_jobinfo->data;
		jobinfo->cleaning = 0;
	} else
		error("_job_fini: job %u had a bad magic, "
		      "this should never happen", nhc_info.jobid);

	unlock_slurmctld(job_write_lock);

	return NULL;
}
