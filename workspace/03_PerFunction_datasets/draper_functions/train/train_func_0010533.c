_print_job_time_end(job_info_t * job, int width, bool right, char* suffix)
{
	if (job == NULL)
		_print_str("END_TIME", width, right, true);
	else if ((job->time_limit == INFINITE) &&
		 (job->end_time > time(NULL)))
		_print_str("NONE", width, right, true);
	else
		_print_time(job->end_time, 0, width, right);
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
