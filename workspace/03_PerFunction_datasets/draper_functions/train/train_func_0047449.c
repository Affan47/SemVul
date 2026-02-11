io_close_all(stepd_step_rec_t *job)
{
	int devnull;
#if 0
	int i;
	for (i = 0; i < job->node_tasks; i++)
		_io_finalize(job->task[i]);
#endif


	debug("Closing debug channel");


	if ((devnull = open("/dev/null", O_RDWR)) < 0) {
		error("Could not open /dev/null: %m");
	} else {
		if (dup2(devnull, STDERR_FILENO) < 0)
			error("Unable to dup /dev/null onto stderr");
	}


	eio_signal_shutdown(job->eio);
}
