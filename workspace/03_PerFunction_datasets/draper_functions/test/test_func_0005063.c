Ns_RWLockRdLock(Ns_RWLock *rwPtr)
{
    RwLock *lockPtr = GetRwLock(rwPtr);

    Ns_MutexLock(&lockPtr->mutex);


    while (lockPtr->lockcnt < 0 || lockPtr->nwriters > 0) {
	lockPtr->nreaders++;
	Ns_CondWait(&lockPtr->rcond, &lockPtr->mutex);
	lockPtr->nreaders--;
    }

    lockPtr->lockcnt++;
    Ns_MutexUnlock(&lockPtr->mutex);
}
