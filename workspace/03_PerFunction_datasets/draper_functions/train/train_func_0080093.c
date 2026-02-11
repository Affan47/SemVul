job_signal_wiki(char *cmd_ptr, int *err_code, char **err_msg)
{
	char *arg_ptr, *sig_ptr, *tmp_char;
	int slurm_rc;
	uint32_t jobid;
	uint16_t sig_num;
	static char reply_msg[128];

	slurmctld_lock_t job_write_lock = {
		NO_LOCK, WRITE_LOCK, WRITE_LOCK, NO_LOCK };

	arg_ptr = strstr(cmd_ptr, "ARG=");
	if (arg_ptr == NULL) {
		*err_code = -300;
		*err_msg = "SIGNALJOB lacks ARG=";
		error("wiki: SIGNALJOB lacks ARG=");
		return -1;
	}
	arg_ptr +=4;
	jobid = strtoul(arg_ptr, &tmp_char, 10);
	if ((tmp_char[0] != '\0') && (!isspace(tmp_char[0]))) {
		*err_code = -300;
		*err_msg = "Invalid ARG value";
		error("wiki: SIGNALJOB has invalid jobid %s",
			arg_ptr);
		return -1;
	}

	sig_ptr = strstr(cmd_ptr, "VALUE=");
	if (sig_ptr == NULL) {
		*err_code = -300;
		*err_msg = "SIGNALJOB lacks VALUE=";
		error("wiki: SIGNALJOB lacks VALUE=");
		return -1;
	}
	sig_ptr += 6;
	sig_num = _xlate_signal(sig_ptr);
	if (sig_num == 0) {
		*err_code = -300;
		*err_msg = "SIGNALJOB has invalid signal value";
		error("wiki: SIGNALJOB has invalid signal value: %s",
			sig_ptr);
		return -1;
	}

	lock_slurmctld(job_write_lock);
	slurm_rc = _job_signal(jobid, sig_num);
	unlock_slurmctld(job_write_lock);
	if (slurm_rc != SLURM_SUCCESS) {
		*err_code = -700;
		*err_msg = slurm_strerror(slurm_rc);
		error("wiki: Failed to signal job %u: %s",
			jobid, slurm_strerror(slurm_rc));
		return -1;
	}

	snprintf(reply_msg, sizeof(reply_msg),
		"job %u signalled", jobid);
	*err_msg = reply_msg;
	return 0;
}
