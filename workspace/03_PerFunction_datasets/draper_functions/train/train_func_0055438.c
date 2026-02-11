TasksCleanup() {
    if (PbrtOptions.nCores == 1)
        return;
#ifdef PBRT_USE_GRAND_CENTRAL_DISPATCH
    return;
#else
    if (!taskQueueMutex || !workerSemaphore)
        return;
    { MutexLock lock(*taskQueueMutex);
    Assert(taskQueue.size() == 0);
    }

    static const int nThreads = NumSystemCores();
    if (workerSemaphore != NULL)
        workerSemaphore->Post(nThreads);

    if (threads != NULL) {
#if !defined(PBRT_IS_WINDOWS)
        for (int i = 0; i < nThreads; ++i) {
            int err = pthread_join(threads[i], NULL);
            if (err != 0)
                Severe("Error from pthread_join: %s", strerror(err));
        }
#else
        WaitForMultipleObjects(nThreads, threads, TRUE, INFINITE);
        for (int i = 0; i < nThreads; ++i) {
            CloseHandle(threads[i]);
        }
#endif
        delete[] threads;
        threads = NULL;
    }
#endif
}
