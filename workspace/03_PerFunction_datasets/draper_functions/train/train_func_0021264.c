globus_l_fork_task_free(
    globus_fork_task_t                  task)
{
    if (task == NULL)
    {
        return;
    }

    if (task->task)
    {
        globus_libc_free(task->task);
    }

    if (task->environment)
    {
        globus_libc_free(task->environment);
    }

    if (task->arguments)
    {
        globus_libc_free(task->arguments);
    }
    if (task->jobid_prefix)
    {
        free(task->jobid_prefix);
    }

    globus_libc_free(task);
}
