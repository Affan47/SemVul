sig_child_handler(int sig_no UNUSED_PARAM)
{
	pid_t pid;
	int l;

	if (verbose)
		bb_error_msg(INFO"sig%s received", "child");
	while ((pid = wait_any_nohang(&wstat)) > 0) {
		for (l = 0; l < dirn; ++l) {
			if (dir[l].ppid == pid) {
				dir[l].ppid = 0;
				processorstop(&dir[l]);
				break;
			}
		}
	}
}
