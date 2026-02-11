condvarWait(condvar_t *condvar, mutex_t *mutex, thread_state_t wtype)
{
    sigjmp_buf jmpbuf;
    int err;

    sys_thread_t *self = sysThreadSelf();


    self->state = wtype;

#ifdef __linux__


     pthread_cleanup_push(intrHandler, NULL);
     if (setjmp(jmpbuf) == 0) {


         thr_setspecific(intrJmpbufkey, &jmpbuf);
         pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);


#else
    thr_setspecific(sigusr1Jmpbufkey, &jmpbuf);
    if (sigsetjmp(jmpbuf, 1) == 0) {
        sigset_t osigset;

        thr_sigsetmask(SIG_UNBLOCK, &sigusr1Mask, &osigset);
again:
#endif
        err = cond_wait((cond_t *) condvar, (mutex_t *) mutex);
        switch(err) {
        case 0:
            err = SYS_OK;
            break;
#ifndef __linux__
        case EINTR:
            goto again;
#endif
        default:
            err = SYS_ERR;
        }
#ifdef __linux__


        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        thr_setspecific(intrJmpbufkey, NULL);
#else
        thr_sigsetmask(SIG_SETMASK, &osigset, NULL);
#endif
    } else {


#ifndef __linux__
         thr_setspecific(sigusr1Jmpbufkey, NULL);
#endif
         err = SYS_INTRPT;
    }
#ifdef __linux__
    pthread_cleanup_pop(0);
#endif


    self->state = RUNNABLE;

    return err;
}
