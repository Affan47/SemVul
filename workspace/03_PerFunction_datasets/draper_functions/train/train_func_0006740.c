start() {

    int status;
    pthread_attr_t thread_attr;

    status = pthread_attr_init( &thread_attr );
    if(status != 0)
    {
        return status;
    }

    PThreadPrivateData *pd = static_cast<PThreadPrivateData *> (_prvData);


    if(pd->stackSize)
    {
#ifdef PTHREAD_STACK_MIN
        if(pd->stackSize < PTHREAD_STACK_MIN)
            pd->stackSize = PTHREAD_STACK_MIN;
#endif
        pthread_attr_setstacksize( &thread_attr, pd->stackSize);
        if(status != 0)
        {
            return status;
        }
    }


    size_t size;
    pthread_attr_getstacksize( &thread_attr, &size);
    if(status != 0)
    {
        return status;
    }
    pd->stackSize = size;


    pd->stackSizeLocked = true;

#ifdef ALLOW_PRIORITY_SCHEDULING

    status = pthread_attr_setinheritsched( &thread_attr,
                       PTHREAD_EXPLICIT_SCHED );

    pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);

#endif

    if(status != 0)
    {
        return status;
    }

    pd->threadStartedBlock.reset();

    status = pthread_create(&(pd->tid), &thread_attr,
                           ThreadPrivateActions::StartThread,
                           static_cast<void *>(this));

    if(status == 0)
    {

        pd->threadStartedBlock.block();

        pd->idSet = true;
    }

    return status;
}
