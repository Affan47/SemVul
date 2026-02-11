read_pid_stats(unsigned int pid, struct pid_stats *pst,
		   unsigned int *thread_nr, unsigned int tgid)
{
	if (read_proc_pid_stat(pid, pst, thread_nr, tgid))
		return 1;

	if (DISPLAY_CMDLINE(pidflag)) {
		if (read_proc_pid_cmdline(pid, pst, tgid))
			return 1;
	}

	if (read_proc_pid_status(pid, pst, tgid))
		return 1;

	if (DISPLAY_STACK(actflag)) {
		if (read_proc_pid_smap(pid, pst, tgid))
			return 1;
	}

	if (DISPLAY_KTAB(actflag)) {
		if (read_proc_pid_fd(pid, pst, tgid))
			return 1;
	}

	if (DISPLAY_IO(actflag))

		return (read_proc_pid_io(pid, pst, tgid));

	return 0;
}
