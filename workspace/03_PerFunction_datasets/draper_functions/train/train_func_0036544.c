gw_rwlock_destroy(RWLock *lock)
{
#ifdef HAVE_PTHREAD_RWLOCK
    int ret;
#endif

    if (!lock)
        return;

#ifdef HAVE_PTHREAD_RWLOCK
    ret = pthread_rwlock_destroy(&lock->rwlock);
    if (ret != 0)
        panic(ret, "Attempt to destroy locked rwlock.");
#else
    gwlist_destroy(lock->rwlock, NULL);
#endif

    if (lock->dynamic)
        gw_free(lock);
}
