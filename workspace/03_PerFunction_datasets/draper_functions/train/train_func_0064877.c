catchSystemSignal(int sig)
{
    if (sig > 0 && sig < NSIG)
    {
        struct sigaction act;

        act.sa_handler = cxxtools_system_application_sighandler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_RESTART;

        if (-1 == ::sigaction(sig, &act, NULL))
        {
            throw SystemError("sigaction failed");
        }

        return true;
    }

    return false;
}
