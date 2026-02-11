_retry(void)
{
	static int  retries = 0;
	static char *msg = "Slurm controller not responding, "
		"sleeping and retrying.";

	if (errno == ESLURM_ERROR_ON_DESC_TO_RECORD_COPY) {
		if (retries == 0)
			error("%s", msg);
		else if (retries < MAX_RETRIES)
			debug("%s", msg);
		else
			return false;
		sleep (++retries);
	} else if (errno == EINTR) {


		debug("Syscall interrupted while allocating resources, "
		      "retrying.");
		return true;
	} else if (opt.immediate &&
		   ((errno == ETIMEDOUT) || (errno == ESLURM_NODES_BUSY))) {
		error("Unable to allocate resources: %s",
		      slurm_strerror(ESLURM_NODES_BUSY));
		error_exit = immediate_exit;
		return false;
	} else {
		error("Unable to allocate resources: %m");
		return false;
	}

	return true;
}
