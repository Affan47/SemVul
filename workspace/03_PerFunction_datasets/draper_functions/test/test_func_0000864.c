_print_fs_priority_weighted(priority_factors_object_t * job, int width,
				bool right, char* suffix)
{
	if (job == NULL)
		_print_str("FAIRSHARE", width, right, true);
	else if (job == (priority_factors_object_t *) -1)
		_print_int(weight_fs, width, right, true);
	else
		_print_int(job->priority_fs, width, right, true);
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
