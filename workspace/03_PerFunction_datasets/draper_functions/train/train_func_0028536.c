shell_name(void)
{
	const char *shell = getenv("SHELL");
	if (access(shell, X_OK))
		shell = "/bin/sh";
	return shell;
}
