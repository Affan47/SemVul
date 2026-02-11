signal_cb (int signum, siginfo_t *info, void *data)
{


    if (getpid () != signal_pid)
        _exit (EXIT_SUCCESS);


    if (write (signal_pipe[1], &info->si_signo, sizeof (int)) < 0 ||
        write (signal_pipe[1], &info->si_pid, sizeof (pid_t)) < 0)
        close (signal_pipe[1]);
}
