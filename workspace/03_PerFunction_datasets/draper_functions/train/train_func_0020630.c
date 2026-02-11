_pty_thread(void *arg)
{
	int fd = -1;
	srun_job_t *job = (srun_job_t *) arg;
	slurm_addr_t client_addr;

	xsignal_unblock(pty_sigarray);
	xsignal(SIGWINCH, _handle_sigwinch);

	if ((fd = slurm_accept_msg_conn(job->pty_fd, &client_addr)) < 0) {
		error("pty: accept failure: %m");
		return NULL;
	}

	while (job->state <= SRUN_JOB_RUNNING) {
		debug2("waiting for SIGWINCH");
		poll(NULL, 0, -1);
		if (winch) {
			set_winsize(job);
			_notify_winsize_change(fd, job);
		}
		winch = 0;
	}
	return NULL;
}
