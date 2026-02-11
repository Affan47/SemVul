detach()
{
    int pid;
    char numbuf[16];
    int pipefd[2];

    if (detached)
	return;
    if (pipe(pipefd) == -1)
	pipefd[0] = pipefd[1] = -1;
    if ((pid = fork()) < 0) {
	error("Couldn't detach (fork failed: %m)");
	die(1);
    }
    if (pid != 0) {

	notify(pidchange, pid);

	if (pidfilename[0])
	    create_pidfile(pid);
	if (linkpidfile[0])
	    create_linkpidfile(pid);
	exit(0);
    }
    setsid();
    chdir("/");
    dup2(fd_devnull, 0);
    dup2(fd_devnull, 1);
    dup2(fd_devnull, 2);
    detached = 1;
    if (log_default)
	log_to_fd = -1;
    slprintf(numbuf, sizeof(numbuf), "%d", getpid());
    script_setenv("PPPD_PID", numbuf, 1);


    close(pipefd[1]);
    complete_read(pipefd[0], numbuf, 1);
    close(pipefd[0]);
}
