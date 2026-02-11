shutdownCapability (Capability *cap USED_IF_THREADS,
                    Task *task USED_IF_THREADS,
                    rtsBool safe USED_IF_THREADS)
{
#if defined(THREADED_RTS)
    nat i;

    task->cap = cap;


    for (i = 0; ; i++) {
        ASSERT(sched_state == SCHED_SHUTTING_DOWN);

	debugTrace(DEBUG_sched,
		   "shutting down capability %d, attempt %d", cap->no, i);
	ACQUIRE_LOCK(&cap->lock);
	if (cap->running_task) {
	    RELEASE_LOCK(&cap->lock);
	    debugTrace(DEBUG_sched, "not owner, yielding");
	    yieldThread();
	    continue;
	}
	cap->running_task = task;

        if (cap->spare_workers) {


            Task *t, *prev;
            prev = NULL;
            for (t = cap->spare_workers; t != NULL; t = t->next) {
                if (!osThreadIsAlive(t->id)) {
                    debugTrace(DEBUG_sched,
                               "worker thread %p has died unexpectedly", (void *)(size_t)t->id);
                    cap->n_spare_workers--;
                    if (!prev) {
                        cap->spare_workers = t->next;
                    } else {
                        prev->next = t->next;
                    }
                    prev = t;
                }
            }
        }

	if (!emptyRunQueue(cap) || cap->spare_workers) {
	    debugTrace(DEBUG_sched,
		       "runnable threads or workers still alive, yielding");
	    releaseCapability_(cap,rtsFalse);
	    RELEASE_LOCK(&cap->lock);
	    yieldThread();
	    continue;
	}


        if (cap->suspended_ccalls && safe) {
	    debugTrace(DEBUG_sched,
		       "thread(s) are involved in foreign calls, yielding");
            cap->running_task = NULL;
	    RELEASE_LOCK(&cap->lock);


            ioManagerDie();
            yieldThread();
            continue;
        }

        traceSparkCounters(cap);
	RELEASE_LOCK(&cap->lock);
	break;
    }


#endif
}
