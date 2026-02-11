_parse_state( char* str, uint16_t* states )
{
	int i;
	char *state_names;

	if ((i = job_state_num(str)) >= 0) {
		*states = (uint16_t) i;
		return SLURM_SUCCESS;
	}

	error ("Invalid job state specified: %s", str);
	state_names = xstrdup(job_state_string(0));
	for (i=1; i<JOB_END; i++) {
		xstrcat(state_names, ",");
		xstrcat(state_names, job_state_string(i));
	}
	xstrcat(state_names, ",");
	xstrcat(state_names, job_state_string(JOB_COMPLETING));
	xstrcat(state_names, ",");
	xstrcat(state_names, job_state_string(JOB_CONFIGURING));
	error ("Valid job states include: %s\n", state_names);
	xfree (state_names);
	return SLURM_ERROR;
}
