Scm_GetSignalHandler(int signum)
{
    if (signum < 0 || signum >= SCM_NSIG) {
        Scm_Error("bad signal number: %d", signum);
    }

    return sigHandlers.handlers[signum];
}
