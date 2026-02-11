_kill_procs(void)
{
	int killed = 0, i, rc, status;

	for (i=0; i<PID_CNT; i++) {
		if (child_pid[i] == 0)
			continue;

		rc = waitpid(child_pid[i], &status, WNOHANG);
		if (rc == 0) {
#ifdef  POWER_SAVE_KILL_PROCS
			error("power_save: killing process %d",
			      child_pid[i]);
			kill((0-child_pid[i]), SIGKILL);
#else
			error("power_save: orphaning process %d",
			      child_pid[i]);
#endif
			killed++;
		} else {

		}
		child_pid[i]  = 0;
		child_time[i] = (time_t) 0;
	}
	return killed;
}
