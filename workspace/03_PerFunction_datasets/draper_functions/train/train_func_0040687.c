hookSignal(int signo, MprSignal *sp)
{
    MprSignalService    *ssp;
    struct sigaction    act, old;
    int                 rc;

    mprAssert(0 < signo && signo < MPR_MAX_SIGNALS);

    ssp = MPR->signalService;
    lock(ssp);
    rc = sigaction(signo, 0, &old);
    if (rc == 0 && old.sa_sigaction != signalHandler) {
        sp->sigaction = old.sa_sigaction;
        ssp->prior[signo] = old;
        memset(&act, 0, sizeof(act));
        act.sa_sigaction = signalHandler;
        act.sa_flags |= SA_SIGINFO | SA_RESTART | SA_NOCLDSTOP;
        act.sa_flags &= ~SA_NODEFER;
        sigemptyset(&act.sa_mask);
        if (sigaction(signo, &act, 0) != 0) {
            mprError("Can't hook signal %d, errno %d", signo, mprGetOsError());
        }
    }
    unlock(ssp);
}
