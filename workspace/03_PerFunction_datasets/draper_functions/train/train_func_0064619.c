is_reachable(const char *host)
{
    int res=0;
    int status;
    pid_t pid;

    if (!host || strcmp(host, "") == 0)
        return 1;

    pid = fork();

    if (pid == 0)
    {
        close(1);
        close(2);
        execlp("ping", "ping", "-c", PING_COUNT, "-i", PING_INTERVAL, "-w", PING_DEADLINE, host, NULL);
    }

    else
    {
        waitpid(pid, &status, 0);
        res = WEXITSTATUS(status);
    }

    return (res == 0);
}
