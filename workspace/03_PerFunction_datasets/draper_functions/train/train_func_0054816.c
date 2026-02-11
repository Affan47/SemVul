_print_step_time_start(job_step_info_t * step, int width, bool right,
			   char* suffix)
{
	if (step == NULL)
		_print_str("START_TIME", width, false, true);
	else
		_print_time(step->start_time, 0, width, right);
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
