_add_run_job(struct cr_record *cr_ptr, uint32_t job_id)
{
	int i;

	if (cr_ptr->run_job_ids == NULL) {
		cr_ptr->run_job_len = RUN_JOB_INCR;
		cr_ptr->run_job_ids = xmalloc(sizeof(uint32_t) *
					      cr_ptr->run_job_len);
		cr_ptr->run_job_ids[0] = job_id;
		return;
	}

	for (i=0; i<cr_ptr->run_job_len; i++) {
		if (cr_ptr->run_job_ids[i])
			continue;

		cr_ptr->run_job_ids[i] = job_id;
		return;
	}


	cr_ptr->run_job_len += RUN_JOB_INCR;
	xrealloc(cr_ptr->run_job_ids, sizeof(uint32_t) * cr_ptr->run_job_len);
	cr_ptr->run_job_ids[i] = job_id;
}
