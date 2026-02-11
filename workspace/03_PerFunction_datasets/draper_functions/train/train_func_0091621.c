PR_WaitCondVar(PRCondVar *cvar, PRIntervalTime timeout)
{
    PRIntn rv;
    PRThread *thred = PR_GetCurrentThread();

    PR_ASSERT(cvar != NULL);

    PR_ASSERT(_PT_PTHREAD_MUTEX_IS_LOCKED(cvar->lock->mutex));
    PR_ASSERT(PR_TRUE == cvar->lock->locked);

    PR_ASSERT(pthread_equal(cvar->lock->owner, pthread_self()));

    if (_PT_THREAD_INTERRUPTED(thred)) goto aborted;


    thred->waiting = cvar;


    if (0 != cvar->lock->notified.length)
        pt_PostNotifies(cvar->lock, PR_FALSE);


    cvar->lock->locked = PR_FALSE;

    if (timeout == PR_INTERVAL_NO_TIMEOUT)
        rv = pthread_cond_wait(&cvar->cv, &cvar->lock->mutex);
    else
        rv = pt_TimedWait(&cvar->cv, &cvar->lock->mutex, timeout);


    PR_ASSERT(PR_FALSE == cvar->lock->locked);
    cvar->lock->locked = PR_TRUE;
    cvar->lock->owner = pthread_self();

    PR_ASSERT(0 == cvar->lock->notified.length);
    thred->waiting = NULL;
    if (_PT_THREAD_INTERRUPTED(thred)) goto aborted;
    if (rv != 0)
    {
        _PR_MD_MAP_DEFAULT_ERROR(rv);
        return PR_FAILURE;
    }
    return PR_SUCCESS;

aborted:
    PR_SetError(PR_PENDING_INTERRUPT_ERROR, 0);
    thred->state &= ~PT_THREAD_ABORTED;
    return PR_FAILURE;
}
