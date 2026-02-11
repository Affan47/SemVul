sms_send(const char *recipient, const char *message)
{
	int pid, fd[2] = { 0, 0 };
	char *tmp;

	if (!config_sms_app) {
		errno = EINVAL;
		return -1;
	}

	if (!recipient || !message) {
		errno = EINVAL;
		return -1;
	}

	if (pipe(fd))
		return -1;

	if (!(pid = fork())) {
		dup2(open("/dev/null", O_RDONLY), 0);

		if (fd[1]) {
			close(fd[0]);
			dup2(fd[1], 2);
			dup2(fd[1], 1);
			close(fd[1]);
		}

		execlp(config_sms_app, config_sms_app, recipient, message, (void *) NULL);
		exit(1);
	}

	if (pid < 0) {
		close(fd[0]);
		close(fd[1]);
		return -1;
	}

	close(fd[1]);

	tmp = saprintf(("%s %s %s"), config_sms_app, recipient, message);
	child_add(&sms_plugin, pid, tmp, sms_child_handler, xstrdup(recipient));
	xfree(tmp);

	return 0;
}
