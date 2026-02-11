child_handler(int signo)
{
	for (;;) {
		int status;
		pid_t pid = waitpid(-1, &status, WNOHANG);

		if (pid > 0) {
			unsigned reaped = children_reaped;
			if (!WIFEXITED(status) || WEXITSTATUS(status) > 0)
				pid = -pid;
			dead_child[reaped % MAX_CHILDREN] = pid;
			children_reaped = reaped + 1;
			write(child_handler_pipe[1], &status, 1);
			continue;
		}
		break;
	}
	signal(SIGCHLD, child_handler);
}
