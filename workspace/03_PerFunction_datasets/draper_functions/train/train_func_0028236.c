signalThread() {
    Log::dbg("Thread wake up signal sending...");

    pthread_mutex_lock(&waitThreadMutex);
    pthread_cond_signal(&waitThreadCond);
    pthread_mutex_unlock(&waitThreadMutex);
    Log::dbg("Thread wake up signal was sent!");
}
