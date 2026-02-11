allocTask (void)
{
    Task *task;

    task = myTask();
    if (task != NULL) {
        return task;
    } else {
        task = newTask(rtsFalse);
#if defined(THREADED_RTS)
        task->id = osThreadId();
#endif
        setMyTask(task);
        return task;
    }
}
