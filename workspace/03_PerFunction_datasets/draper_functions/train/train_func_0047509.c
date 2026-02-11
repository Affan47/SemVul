task_pool_delete(task_pool_handle_t handle)
{
    int rc = 0;
    task_pool_t *tp = (task_pool_t*)handle;

    if(!tp) return -1;

    rc = task_pool_stop(handle);
    pthread_cond_destroy(&tp->cond);
    pthread_mutex_destroy(&tp->mutex);
    free(tp->stats);
    free(tp);
    return rc;
}
