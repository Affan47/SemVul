exitScheduler (rtsBool wait_foreign USED_IF_THREADS)

{
    Task *task = NULL;

    task = newBoundTask();


    if (sched_state < SCHED_SHUTTING_DOWN) {
	sched_state = SCHED_INTERRUPTING;
        Capability *cap = task->cap;
        waitForReturnCapability(&cap,task);
        scheduleDoGC(&cap,task,rtsTrue);
        ASSERT(task->incall->tso == NULL);
        releaseCapability(cap);
    }
    sched_state = SCHED_SHUTTING_DOWN;

    shutdownCapabilities(task, wait_foreign);


    boundTaskExiting(task);
}
