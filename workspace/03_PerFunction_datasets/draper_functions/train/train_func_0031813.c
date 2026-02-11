br_queue_remove_range (BrQueue *queue,
                       int      index,
                       int      count)
{
    BrQueuePrivate *priv;

    g_return_if_fail (IS_BR_QUEUE (queue));

    priv = queue->priv;

    org_moblin_BognorRegis_Queue_remove_range_async (priv->proxy, index,
                                                     count, async_reply, queue);
}
