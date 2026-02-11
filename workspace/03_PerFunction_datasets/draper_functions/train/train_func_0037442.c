get_next_job_id(void)
{
	uint32_t next_id;

	job_id_sequence = MAX(job_id_sequence, slurmctld_conf.first_job_id);
	next_id = job_id_sequence + 1;
	if (next_id >= slurmctld_conf.max_job_id)
		next_id = slurmctld_conf.first_job_id;
	return next_id;
}
