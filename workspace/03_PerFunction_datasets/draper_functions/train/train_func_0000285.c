close_console_window(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
	return RC_OS_FORK_FAILURE;
    }

    if (pid == 0)
    {
	fclose(stdin);
	fclose(stderr);
	setsid();
	if (-1 == chdir("/"))
	{
		logit(LOG_WARNING, MODULE_TAG "Failed changing cwd to /: %s", strerror(errno));
	}
	umask(0);

	return RC_OK;
    }

    exit(0);

    return RC_OK;
}
