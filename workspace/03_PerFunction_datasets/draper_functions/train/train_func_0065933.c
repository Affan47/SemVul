fastEnableSuspend(Thread *thread) {

    thread->suspend_state = SUSP_NONE;
    MBARRIER();

    if(thread->suspend) {
        sigset_t mask;

        sigemptyset(&mask);
        sigaddset(&mask, SIGUSR1);
        pthread_sigmask(SIG_BLOCK, &mask, NULL);

        TRACE("Thread %p id: %d is fast self suspending\n",
              thread, thread->id);

        suspendLoop(thread);

        TRACE("Thread %p id: %d resumed\n", thread, thread->id);

        pthread_sigmask(SIG_UNBLOCK, &mask, NULL);
    }
}
