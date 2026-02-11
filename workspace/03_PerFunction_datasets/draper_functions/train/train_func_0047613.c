_fork_command(char **command)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		error("fork failed: %m");
	} else if (pid == 0) {

		setpgid(getpid(), 0);


		xsignal(SIGINT, SIG_DFL);
		xsignal(SIGQUIT, SIG_DFL);
		xsignal(SIGTTIN, SIG_DFL);
		xsignal(SIGTTOU, SIG_DFL);

		execvp(command[0], command);


		error("Unable to exec command \"%s\"", command[0]);
		exit(error_exit);
	}

	return pid;
}
