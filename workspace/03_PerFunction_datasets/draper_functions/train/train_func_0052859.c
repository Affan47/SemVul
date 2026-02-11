init_sigchld(int sig)
{
    sighandler_t oldfunc;
#if USE_TRAP_MASK
    sigset_t mask;
    sigset_t fullmask;


    sigfillset(&fullmask);
    pthread_sigmask(SIG_BLOCK, &fullmask, &mask);
#endif

    oldfunc = ruby_signal(sig, SIG_DFL);
    if (oldfunc != SIG_DFL && oldfunc != SIG_IGN) {
	ruby_signal(sig, oldfunc);
    } else {
	GET_VM()->trap_list[sig].cmd = 0;
    }

#if USE_TRAP_MASK
    sigdelset(&mask, sig);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);
    trap_last_mask = mask;
#endif
}
