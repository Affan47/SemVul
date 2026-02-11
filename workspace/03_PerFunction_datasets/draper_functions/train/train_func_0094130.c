Ns_RWLockDestroy(Ns_RWLock *rwPtr)
{
    RwLock *lockPtr = (RwLock *) *rwPtr;

    if (lockPtr != NULL) {
    	Ns_MutexDestroy(&lockPtr->mutex);
    	Ns_CondDestroy(&lockPtr->rcond);
    	Ns_CondDestroy(&lockPtr->wcond);
    	ns_free(lockPtr);
    	*rwPtr = NULL;
    }
}
