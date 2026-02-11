markSignal(int sig)
#endif
{
    pendingSig++;
    sigaddset(&pendingSignals,sig);
    if (sig==SIGTERM)
	pendingTerm=1;
#ifdef __hpux
    if (scp && scp->sc_syscall==SYS_select) {
	scp->sc_syscall_action=SIG_RETURN;
    }
#endif
}
