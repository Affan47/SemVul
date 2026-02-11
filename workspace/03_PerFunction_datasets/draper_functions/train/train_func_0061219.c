threadUnpark(Thread *thread) {
    if(thread->park_state != PARK_PERMIT) {


        while(pthread_mutex_trylock(&thread->park_lock))
            sched_yield();


        if(thread->park_state != PARK_PERMIT &&
                  thread->park_state++ == PARK_BLOCKED)
            pthread_cond_signal(&thread->park_cv);

        pthread_mutex_unlock(&thread->park_lock);
    }
}
