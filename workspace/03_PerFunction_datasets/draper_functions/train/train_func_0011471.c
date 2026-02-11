PKIX_PL_IsReaderLockHeld(
        PKIX_PL_RWLock *lock,
        PKIX_Boolean *pIsHeld,
        void *plContext)
{
        PKIX_ENTER(RWLOCK, "PKIX_PL_IsReaderLockHeld");
        PKIX_NULLCHECK_TWO(lock, pIsHeld);

        *pIsHeld = (lock->readCount > 0)?PKIX_TRUE:PKIX_FALSE;

        PKIX_RETURN(RWLOCK);
}
