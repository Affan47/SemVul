Perl_sharedsv_cond_timedwait(perl_cond *cond, perl_mutex *mut, double abs)
{
#if defined(NETWARE) || defined(FAKE_THREADS) || defined(I_MACH_CTHREADS)
    Perl_croak_nocontext("cond_timedwait not supported on this platform");
#else
#  ifdef WIN32
    int got_it = 0;

    cond->waiters++;
    MUTEX_UNLOCK(mut);

    switch (WaitForSingleObject(cond->sem, S_abs_2_rel_milli(abs))) {
        case WAIT_OBJECT_0:   got_it = 1; break;
        case WAIT_TIMEOUT:                break;
        default:

            Perl_croak_nocontext("panic: cond_timedwait (%ld)",GetLastError());
            break;
    }
    MUTEX_LOCK(mut);
    cond->waiters--;
    return (got_it);
#  else
#    ifdef OS2
    int rc, got_it = 0;
    STRLEN n_a;

    ABS2RELMILLI(abs);

    if ((rc = DosResetEventSem(*cond,&n_a)) && (rc != ERROR_ALREADY_RESET))
        Perl_rc = rc, croak_with_os2error("panic: cond_timedwait-reset");
    MUTEX_UNLOCK(mut);
    if (CheckOSError(DosWaitEventSem(*cond,abs))
        && (rc != ERROR_INTERRUPT))
        croak_with_os2error("panic: cond_timedwait");
    if (rc == ERROR_INTERRUPT) errno = EINTR;
    MUTEX_LOCK(mut);
    return (got_it);
#    else
    struct timespec ts;
    int got_it = 0;

    ts.tv_sec = (long)abs;
    abs -= (NV)ts.tv_sec;
    ts.tv_nsec = (long)(abs * 1000000000.0);

    switch (pthread_cond_timedwait(cond, mut, &ts)) {
        case 0:         got_it = 1; break;
        case ETIMEDOUT:             break;
#ifdef OEMVS
        case -1:
            if (errno == ETIMEDOUT || errno == EAGAIN)
                break;
#endif
        default:
            Perl_croak_nocontext("panic: cond_timedwait");
            break;
    }
    return (got_it);
#    endif
#  endif
#endif
}
