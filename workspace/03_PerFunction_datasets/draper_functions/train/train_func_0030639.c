stopCaching() {

    cacheStateLock.lock();

    threadSend(STOP);


    while (cacheState == CACHE_STATE_ACTIVE) {
        cacheStateLock.unlock();
        usleep(10000);
        cacheStateLock.lock();
    }
    cacheStateLock.unlock();
}
