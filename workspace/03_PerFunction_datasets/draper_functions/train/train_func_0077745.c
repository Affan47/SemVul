gw_prioqueue_len(gw_prioqueue_t *queue)
{
    long len;

    if (queue == NULL)
        return 0;

    queue_lock(queue);
    len = queue->len - 1;
    queue_unlock(queue);

    return len;
}
