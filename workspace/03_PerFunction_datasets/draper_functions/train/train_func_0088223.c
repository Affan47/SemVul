job_submit(struct job_descriptor *job_desc, uint32_t submit_uid)
{
	char *std_out, *tok;
	uint32_t my_job_id = get_next_job_id();

	_xlate_dependency(job_desc, submit_uid, my_job_id);

	if (job_desc->account)
		_add_env2(job_desc, "PBS_ACCOUNT", job_desc->account);

	if (job_desc->script) {


	} else {


	}

	if (job_desc->partition)
		_add_env2(job_desc, "PBS_QUEUE", job_desc->partition);

	if (job_desc->std_out)
		std_out = job_desc->std_out;
	else
		std_out = "slurm-%j.out";
	if (job_desc->comment)
		xstrcat(job_desc->comment, ",");
	xstrcat(job_desc->comment, "stdout=");
	if (std_out && (std_out[0] != '/') && job_desc->work_dir) {
		xstrcat(job_desc->comment, job_desc->work_dir);
		xstrcat(job_desc->comment, "/");
	}
	tok = strstr(std_out, "%j");
	if (tok) {
		char buf[16], *tok2;
		char *tmp = xstrdup(std_out);
		tok2 = strstr(tmp, "%j");
		tok2[0] = '\0';
		snprintf(buf, sizeof(buf), "%u", my_job_id);
		xstrcat(tmp, buf);
		xstrcat(tmp, tok + 2);
		xstrcat(job_desc->comment, tmp);
		xfree(tmp);
	} else {
		xstrcat(job_desc->comment, std_out);
	}

	return SLURM_SUCCESS;
}
