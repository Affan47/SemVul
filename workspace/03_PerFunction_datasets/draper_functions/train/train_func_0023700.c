releaseCapabilityAndQueueWorker (Capability* cap USED_IF_THREADS)
{
    Task *task;

    ACQUIRE_LOCK(&cap->lock);

    task = cap->running_task;


    ASSERT(!task->stopped);


    if (!isBoundTask(task))
    {
        if (cap->n_spare_workers < MAX_SPARE_WORKERS)
        {
            task->next = cap->spare_workers;
            cap->spare_workers = task;
            cap->n_spare_workers++;
        }
        else
        {
            debugTrace(DEBUG_sched, "%d spare workers already, exiting",
                       cap->n_spare_workers);
            releaseCapability_(cap,rtsFalse);

            workerTaskStop(task);
            RELEASE_LOCK(&cap->lock);
            shutdownThread();
        }
    }


    releaseCapability_(cap,rtsFalse);

    RELEASE_LOCK(&cap->lock);
}
