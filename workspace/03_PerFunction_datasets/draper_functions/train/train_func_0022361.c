_set_job_id(struct job_record *job_ptr)
{
	int i;
	uint32_t new_id;

	job_id_sequence = MAX(job_id_sequence, slurmctld_conf.first_job_id);

	xassert(job_ptr);
	xassert (job_ptr->magic == JOB_MAGIC);
	if ((job_ptr->partition == NULL)
	    || (strlen(job_ptr->partition) == 0))
		fatal("_set_job_id: partition not set");


	for (i = 0; i < 1000; i++) {
		if (++job_id_sequence >= slurmctld_conf.max_job_id)
			job_id_sequence = slurmctld_conf.first_job_id;
		new_id = job_id_sequence;
		if (find_job_record(new_id) == NULL) {
			job_ptr->job_id = new_id;
			return;
		}
	}
	fatal("We have exhausted our supply of valid job id values."
	      "FirstJobId=%u MaxJobId=%u", slurmctld_conf.first_job_id,
	      slurmctld_conf.max_job_id);
}
