PKIX_PL_AcquireWriterLock(
        PKIX_PL_RWLock *lock,
        void *plContext)
{
        PKIX_ENTER(RWLOCK, "PKIX_PL_AcquireWriterLock");
        PKIX_NULLCHECK_ONE(lock);

        PKIX_RWLOCK_DEBUG("\tCalling PR_RWLock_Wlock\n");
        (void) PR_RWLock_Wlock(lock->lock);

        if (lock->readCount > 0) {
                PKIX_ERROR(PKIX_LOCKHASNONZEROREADCOUNT);
        }


        lock->writeLocked = PKIX_TRUE;

cleanup:

        PKIX_RETURN(RWLOCK);
}
