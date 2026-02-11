_cancel_job(uint32_t jobid, char *comment_ptr,
			    int *err_code, char **err_msg)
{
	int rc = 0, slurm_rc;

	slurmctld_lock_t job_write_lock = {
		NO_LOCK, WRITE_LOCK, NO_LOCK, NO_LOCK };
	struct job_record *job_ptr = find_job_record(jobid);

	lock_slurmctld(job_write_lock);
	if (job_ptr == NULL) {
		*err_code = -700;
		*err_msg = "No such job";
		error("wiki: Failed to find job %u", jobid);
		rc = -1;
		goto fini;
	}

	if (comment_ptr) {
		char *reserved = strstr(comment_ptr, "RESERVED:");
		if (reserved && job_ptr->details) {
			reserved += 9;
			job_ptr->details->reserved_resources =
				strtol(reserved, NULL, 10);
		}
		xfree(job_ptr->comment);
		job_ptr->comment = xstrdup(comment_ptr);
	}

	slurm_rc = job_signal(jobid, SIGKILL, 0, 0, false);
	if (slurm_rc != SLURM_SUCCESS) {
		*err_code = -700;
		*err_msg = slurm_strerror(slurm_rc);
		error("wiki: Failed to cancel job %u: %s",
			jobid, slurm_strerror(slurm_rc));
		rc = -1;
		goto fini;
	}

	info("wiki: cancel job %u", jobid);

 fini:	unlock_slurmctld(job_write_lock);
	return rc;
}
