_print_job_time_limit(job_info_t * job, int width, bool right,
			  char* suffix)
{
	if (job == NULL)
		_print_str("TIMELIMIT", width, right, true);
	else if (job->time_limit == INFINITE)
		_print_str("UNLIMITED", width, right, true);
	else if (job->time_limit == NO_VAL)
		_print_str("NOT_SET", width, right, true);
	else
		_print_secs((job->time_limit*60), width, right, false);
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
