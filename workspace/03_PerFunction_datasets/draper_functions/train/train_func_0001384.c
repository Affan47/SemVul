setNumCapabilities (nat new_n_capabilities USED_IF_THREADS)
{
#if !defined(THREADED_RTS)
    if (new_n_capabilities != 1) {
        errorBelch("setNumCapabilities: not supported in the non-threaded RTS");
    }
    return;
#elif defined(NOSMP)
    if (new_n_capabilities != 1) {
        errorBelch("setNumCapabilities: not supported on this platform");
    }
    return;
#else
    Task *task;
    Capability *cap;
    nat sync;
    StgTSO* t;
    nat g, n;
    Capability *old_capabilities = NULL;

    if (new_n_capabilities == enabled_capabilities) return;

    debugTrace(DEBUG_sched, "changing the number of Capabilities from %d to %d",
               enabled_capabilities, new_n_capabilities);

    cap = rts_lock();
    task = cap->running_task;

    do {
        sync = requestSync(&cap, task, SYNC_OTHER);
    } while (sync);

    acquireAllCapabilities(cap,task);

    pending_sync = 0;

    if (new_n_capabilities < enabled_capabilities)
    {


        for (n = new_n_capabilities; n < enabled_capabilities; n++) {
            capabilities[n].disabled = rtsTrue;
            traceCapDisable(&capabilities[n]);
        }
        enabled_capabilities = new_n_capabilities;
    }
    else
    {


        for (n = enabled_capabilities;
             n < new_n_capabilities && n < n_capabilities; n++) {
            capabilities[n].disabled = rtsFalse;
            traceCapEnable(&capabilities[n]);
        }
        enabled_capabilities = n;

        if (new_n_capabilities > n_capabilities) {
#if defined(TRACING)


            tracingAddCapapilities(n_capabilities, new_n_capabilities);
#endif


            old_capabilities = moreCapabilities(n_capabilities, new_n_capabilities);


            cap = &capabilities[cap->no];


            storageAddCapabilities(n_capabilities, new_n_capabilities);


            updateCapabilityRefs();


            for (g = 0; g < RtsFlags.GcFlags.generations; g++) {
                for (t = generations[g].threads; t != END_TSO_QUEUE; t = t->global_link) {
                    t->cap = &capabilities[t->cap->no];
                }
            }
        }
    }


    releaseAllCapabilities(cap,task);


    startWorkerTasks(n_capabilities, new_n_capabilities);


    if (new_n_capabilities > n_capabilities) {
        n_capabilities = enabled_capabilities = new_n_capabilities;
    }


    if (old_capabilities) {
        stgFree(old_capabilities);
    }

    rts_unlock(cap);

#endif
}
