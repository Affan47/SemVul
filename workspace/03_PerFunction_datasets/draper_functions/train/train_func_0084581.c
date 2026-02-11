_print_job_group_name(job_info_t * job, int width, bool right, char* suffix)
{
	struct group *group_info = NULL;

	if (job == NULL)
		_print_str("GROUP", width, right, true);
	else {
		group_info = getgrgid((gid_t) job->group_id);
		if (group_info && group_info->gr_name[0])
			_print_str(group_info->gr_name, width, right, true);
		else
			_print_int(job->group_id, width, right, true);
	}
	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
