boinc_set_signal_handler(int sig, handler_t handler) {
#if HAVE_SIGACTION
    struct sigaction temp;
    sigaction(sig, NULL, &temp);
    if (temp.sa_handler != SIG_IGN) {
        temp.sa_handler = (void (*)(int))handler;
        sigaction(sig, &temp, NULL);
    }
#else
    void (*temp)(int);
    temp = signal(sig, boinc_catch_signal);
    if (temp == SIG_IGN) {
        signal(sig, SIG_IGN);
    }
#endif
}
