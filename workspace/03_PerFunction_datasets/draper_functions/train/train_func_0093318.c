suspendThread(Thread *thread) {
    thread->suspend = TRUE;
    MBARRIER();

    if(thread->suspend_state == SUSP_NONE) {
        TRACE("Sending suspend signal to thread %p id: %d\n",
              thread, thread->id);
        pthread_kill(thread->tid, SIGUSR1);
    }

    while(thread->suspend_state != SUSP_BLOCKING &&
          thread->suspend_state != SUSP_SUSPENDED) {
        TRACE("Waiting for thread %p id: %d to suspend\n",
              thread, thread->id);
        sched_yield();
    }
}
