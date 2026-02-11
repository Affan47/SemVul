elvis_system(cmd)
	char	*cmd;
{
	int	status;


	if (*o_warn && tstflag(file, MODIFIED))
	{
		if (mode == MODE_VI)
		{
			mode = MODE_COLON;
		}
		msg("Warning: \"%s\" has been modified but not yet saved", origname);
	}

	signal(SIGINT, SIG_IGN);
	switch (fork())
	{
	  case -1:
		msg("fork() failed");
		status = -1;
		break;

	  case 0:

		for (status = 3; status < 60 && (close(status), errno != EINVAL); status++)
		{
		}

		signal(SIGINT, SIG_DFL);
		if (cmd == o_shell)
		{
			execle(o_shell, o_shell, (char *)0, environ);
		}
		else
		{
			execle(o_shell, o_shell, "-c", cmd, (char *)0, environ);
		}
		msg("execle(\"%s\", ...) failed", o_shell);
		exit(1);

	  default:
		wait(&status);
		signal(SIGINT, trapint);
	}

	return status;
}
