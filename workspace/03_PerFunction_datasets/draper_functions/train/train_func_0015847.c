RunWait(Callback **firstPtrPtr, Ns_Thread *threadPtr, Ns_Time *toPtr)
{
    int status;

    status = NS_OK;
    Ns_MutexLock(&lock);
    while (status == NS_OK && *firstPtrPtr != NULL) {
	status = Ns_CondTimedWait(&cond, &lock, toPtr);
    }
    Ns_MutexUnlock(&lock);
    if (status != NS_OK) {
	Ns_Log(Warning, "callbacks: timeout waiting for shutdown procs");
    } else if (*threadPtr != NULL) {
	Ns_ThreadJoin(threadPtr, NULL);
    }
}
