synctask_destroy (struct synctask *task)
{
        if (!task)
                return;

        if (task->stack)
                FREE (task->stack);
        FREE (task);
}
