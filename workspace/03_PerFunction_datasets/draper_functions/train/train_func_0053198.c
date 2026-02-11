_print_job_job_id(priority_factors_object_t * job, int width,
		      bool right, char* suffix)
{
	if (job == NULL)
		_print_str("JOBID", width, right, true);
	else if (job == (priority_factors_object_t *) -1)
		_print_str("Weights", width, right, true);
	else {
		char id[FORMAT_STRING_SIZE];
		snprintf(id, FORMAT_STRING_SIZE, "%u", job->job_id);
		_print_str(id, width, right, true);
	}
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
