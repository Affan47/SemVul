MT_AbortTasks(void)
{
    Task *task;

    while ((task = MT_GetTask()) != NULL)
        MT_TaskDone(task);

    td.result = -1;
}
