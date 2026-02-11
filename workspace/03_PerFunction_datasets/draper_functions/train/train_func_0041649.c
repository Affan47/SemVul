my_system(command, hide)
    const char *command;
    int hide;
{
    pid_t pid;
    int status;
    FILE *stdout_log=NULL;
    FILE *stderr_log=NULL;
    int stdout_log_fd, stderr_log_fd;
    int old_stdout=-1, old_stderr=-1;


    if (command == NULL)
	return 1;

    remove_log();

    if(hide)
    {


	old_stdout = dup(1);
	old_stderr = dup(2);

	close(1);
	close(2);

	strcpy(stdout_log_name,stdout_log_template);
	stdout_log_fd = mkstemp(stdout_log_name);
	if(stdout_log_fd != -1)
	    stdout_log = fdopen(stdout_log_fd, "w");

	strcpy(stderr_log_name,stderr_log_template);
	stderr_log_fd = mkstemp(stderr_log_name);
	if(stderr_log_fd != -1)
	    stderr_log = fdopen(stderr_log_fd, "w");

	if(!stdout_log || !stderr_log)
	{
	    if(stdout_log)
		fclose(stdout_log);
	    if(stderr_log)
		fclose(stderr_log);

	    remove_log();

	    dup(old_stdout);
	    dup(old_stderr);

	    close(old_stdout);
	    close(old_stderr);
	    return -1;
	}
    }


    pid = fork();

    if (pid < 0)
	status = -1;
    else if (pid == 0)
    {

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (hide)
	{


	    if (strncmp(command, "rpm ", 4) != 0)
		close(0);
	}

	execle("/bin/sh", "sh", "-c", command, (char *)NULL, environ);


	_exit(127);
    }
    else
    {

	if(hide)
	{
	    if(stdout_log)
		fclose(stdout_log);
	    if(stderr_log)
		fclose(stderr_log);
	    dup(old_stdout);
	    dup(old_stderr);

	    close(old_stdout);
	    close(old_stderr);
	}
	while (wait(&status) != pid);
    }


    return status;
}
