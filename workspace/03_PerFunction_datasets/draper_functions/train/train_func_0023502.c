ipmi_reap(struct ipmi *ipmi)
{
	if (ipmi->i_pid >= 0) {
		dbg_printf(ipmi, 2, "Reaping pid %d\n", ipmi->i_pid);
		kill(ipmi->i_pid, 9);
		waitpid(ipmi->i_pid, NULL, 0);
	}
	ipmi->i_pid = -1;
	if (ipmi->i_rdfd >= 0) {
		close(ipmi->i_rdfd);
		ipmi->i_rdfd = -1;
	}
	if (ipmi->i_wrfd >= 0) {
		close(ipmi->i_wrfd);
		ipmi->i_wrfd = -1;
	}
	return 0;
}
