pclose_check(FILE * stream)
{
	int exitstatus;

	exitstatus = pclose(stream);
	if (exitstatus == 0)
		return 0;

	if (exitstatus == -1) {

		perror("pclose failed");
	} else if (WIFEXITED(exitstatus))
		log_warning_exec_err(_("child process exited with exit code %d"),
			  WEXITSTATUS(exitstatus));
	else if (WIFSIGNALED(exitstatus))
#if defined(WIN32)
		log_warning_exec_err(_("child process was terminated by exception 0x%X"),
			  WTERMSIG(exitstatus));
#elif defined(HAVE_DECL_SYS_SIGLIST) && HAVE_DECL_SYS_SIGLIST
	{
		char str[256];

		snprintf(str, sizeof(str), "%d: %s", WTERMSIG(exitstatus),
			 WTERMSIG(exitstatus) < NSIG ?
			 sys_siglist[WTERMSIG(exitstatus)] : "(unknown)");
		log_warning_exec_msg(_("child process was terminated by signal %s"), str);
	}
#else
		log_warning_exe_err(_("child process was terminated by signal %d"),
			  WTERMSIG(exitstatus));
#endif
	else
		log_warning_exec_err(_("child process exited with unrecognized status %d"),
			  exitstatus);

	return -1;
}
