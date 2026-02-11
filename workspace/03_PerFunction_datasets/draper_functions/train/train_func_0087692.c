reap_procs()
{
	wait_status_t	w;
	register pid_t	pid;

	for (;;) {
		pid = wait_opt(&w, (WNOHANG | WUNTRACED));
		if (pid <= 0) {
			if (procs_to_reap) {
				resetsighandler(SIGCHLD, sigchld_handler);
				procs_to_reap = NO;

			} else {
				break;
			}
		} else {
			kill_off(pid, w);
		}
	}
}
