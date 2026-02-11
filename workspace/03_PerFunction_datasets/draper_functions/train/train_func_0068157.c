MT_GetTask(void)
{
    Task *task = NULL;

    Mutex_Lock(td.queueLock, "get task");

    if (g_list_length(td.tasks) > 0) {
        task = (Task *) g_list_first(td.tasks)->data;
        td.tasks = g_list_delete_link(td.tasks, g_list_first(td.tasks));
        if (g_list_length(td.tasks) == 0) {
            ResetManualEvent(td.activity);
        }
    }

    multi_debug("get task: release");
    Mutex_Release(td.queueLock);

    return task;
}
