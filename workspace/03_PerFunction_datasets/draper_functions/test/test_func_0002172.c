workerTaskStop (Task *task)
{
    DEBUG_ONLY( OSThreadId id );
    DEBUG_ONLY( id = osThreadId() );
    ASSERT(task->id == id);
    ASSERT(myTask() == task);

    ACQUIRE_LOCK(&all_tasks_mutex);

    if (task->all_prev) {
        task->all_prev->all_next = task->all_next;
    } else {
        all_tasks = task->all_next;
    }
    if (task->all_next) {
        task->all_next->all_prev = task->all_prev;
    }

    currentWorkerCount--;

    RELEASE_LOCK(&all_tasks_mutex);

    freeTask(task);
}
