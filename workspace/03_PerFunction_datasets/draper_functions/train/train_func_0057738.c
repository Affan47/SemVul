sigchild(int s)
{
    int status, pid;


    do
    {
	pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0 && verbose) DNETLOG((LOG_INFO, "Reaped child process %d\n", pid));
    }
    while (pid > 0);
}
