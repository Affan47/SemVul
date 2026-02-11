LogChildExit(int lev, const char *procname, int pid, int exitstatus)
{
	if (WIFEXITED(exitstatus))
		ereport(lev,


				(errmsg("%s (PID %d) exited with exit code %d",
						procname, pid, WEXITSTATUS(exitstatus))));
	else if (WIFSIGNALED(exitstatus))
		ereport(lev,


				(errmsg("%s (PID %d) was terminated by signal %d",
						procname, pid, WTERMSIG(exitstatus))));
	else
		ereport(lev,


				(errmsg("%s (PID %d) exited with unexpected status %d",
						procname, pid, exitstatus)));
}
