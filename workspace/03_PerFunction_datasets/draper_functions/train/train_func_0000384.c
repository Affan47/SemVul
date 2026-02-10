gs_job_scan(void)
{
	if (slurmctld_conf.debug_flags & DEBUG_FLAG_GANG)
		info("gang: entering gs_job_scan");
	pthread_mutex_lock(&data_mutex);
	_scan_slurm_job_list();
	pthread_mutex_unlock(&data_mutex);

	_preempt_job_dequeue();
	if (slurmctld_conf.debug_flags & DEBUG_FLAG_GANG)
		info("gang: leaving gs_job_scan");

	return SLURM_SUCCESS;
}
