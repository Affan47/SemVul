unblock_signal(int nr)
{
    sigset_t mysigset;
    if (sigemptyset(&mysigset) == -1)
        syserr("sigemptyset\n");
    if (sigaddset(&mysigset, SIGPROF) == -1)
        syserr("sigaddset\n");
    if (sigprocmask(SIG_UNBLOCK, &mysigset, NULL) == -1)
        syserr("sigprocmask\n");
}
