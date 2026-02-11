vrrp_script_thread(thread_t * thread)
{
	vrrp_script_t *vscript = THREAD_ARG(thread);
	int status, ret;
	pid_t pid;


	thread_add_timer(thread->master, vrrp_script_thread, vscript,
			 vscript->interval);


	pid = fork();


	if (pid < 0) {
		log_message(LOG_INFO, "Failed fork process");
		return -1;
	}


	if (pid) {
		thread_add_child(thread->master, vrrp_script_child_thread,
				 vscript, pid,
				 (vscript->timeout) ? vscript->timeout : vscript->interval);
		return 0;
	}


	signal_handler_destroy();
	closeall(0);
	open("/dev/null", O_RDWR);
	ret = dup(0);
	if (ret < 0) {
		log_message(LOG_INFO, "dup(0) error");
	}

	ret = dup(0);
	if (ret < 0) {
		log_message(LOG_INFO, "dup(0) error");
	}

	status = system_call(vscript->script);

	if (status < 0 || !WIFEXITED(status))
		status = 0;
	else
		status = WEXITSTATUS(status);

	exit(status);
}
