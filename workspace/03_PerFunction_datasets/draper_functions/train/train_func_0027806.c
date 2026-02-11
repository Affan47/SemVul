reap_child(int sig UNUSED_PARAM)
{
	pid_t pid;
	int status;
	servtab_t *sep;
	int save_errno = errno;

	for (;;) {
		pid = wait_any_nohang(&status);
		if (pid <= 0)
			break;
		for (sep = serv_list; sep; sep = sep->se_next) {
			if (sep->se_wait != pid)
				continue;

			if (WIFEXITED(status) && WEXITSTATUS(status))
				bb_error_msg("%s: exit status %u",
						sep->se_program, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				bb_error_msg("%s: exit signal %u",
						sep->se_program, WTERMSIG(status));
			sep->se_wait = 1;
			add_fd_to_set(sep->se_fd);
			break;
		}
	}
	errno = save_errno;
}
