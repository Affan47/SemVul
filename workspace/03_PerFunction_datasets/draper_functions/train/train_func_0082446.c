_copy_job_desc_to_file(job_desc_msg_t * job_desc, uint32_t job_id)
{
	int error_code = 0;
	char *dir_name, job_dir[32], *file_name;
	DEF_TIMERS;

	START_TIMER;

	dir_name = slurm_get_state_save_location();


	sprintf(job_dir, "/job.%u", job_id);
	xstrcat(dir_name, job_dir);
	if (mkdir(dir_name, 0700)) {
		error("mkdir(%s) error %m", dir_name);
		xfree(dir_name);
		return ESLURM_WRITING_TO_FILE;
	}


	file_name = xstrdup(dir_name);
	xstrcat(file_name, "/environment");
	error_code = _write_data_array_to_file(file_name,
					       job_desc->environment,
					       job_desc->env_size);
	xfree(file_name);

	if (error_code == 0) {

		file_name = xstrdup(dir_name);
		xstrcat(file_name, "/script");
		error_code = _write_data_to_file(file_name, job_desc->script);
		xfree(file_name);
	}

	xfree(dir_name);
	END_TIMER2("_copy_job_desc_to_file");
	return error_code;
}
