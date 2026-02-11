task_pool_wake(task_pool_handle_t handle)
{
    task_pool_t *tp = (task_pool_t *) handle;

    if(!tp) return -1;

    pthread_mutex_lock(&tp->mutex);


    if (!tp->num_idle_tasks) task_pool_new_task(tp);

    pthread_cond_broadcast(&tp->cond);

    pthread_mutex_unlock(&tp->mutex);

    return 0;
}
