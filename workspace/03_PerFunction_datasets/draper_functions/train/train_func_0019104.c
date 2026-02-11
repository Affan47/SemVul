pfs_paranoia_killall()
{
	pid_t *pid_ptr = shared_table;
	while((*pid_ptr) != 0) {
		if((*pid_ptr != 1) && (kill(*pid_ptr, SIGKILL) == -1)) {
			debug(D_NOTICE, "unable to kill process %d due to parrot death", *pid_ptr);
		}
		debug(D_PROCESS, "killing %d due to parrot death", *pid_ptr);
		pid_ptr++;
	}
	return 0;
}
