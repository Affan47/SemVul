register_signal(int sig, void (*func) (int))
{

    switch (sig) {
#if defined(SIGCHLD)
    case SIGCHLD:
#ifdef HAVE_SIGACTION
        {
            static struct sigaction act;
            act.sa_handler = agent_SIGCHLD_handler;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            sigaction(SIGCHLD, &act, NULL);
        }
#else
        signal(SIGCHLD, agent_SIGCHLD_handler);
#endif
        break;
#endif
    default:
        snmp_log(LOG_CRIT,
                 "register_signal: signal %d cannot be handled\n", sig);
        return SIG_REGISTRATION_FAILED;
    }

    external_signal_handler[sig] = func;
    external_signal_scheduled[sig] = 0;

    DEBUGMSGTL(("register_signal", "registered signal %d\n", sig));
    return SIG_REGISTERED_OK;
}
