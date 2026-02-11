gw_prioqueue_destroy(gw_prioqueue_t *queue, void(*item_destroy)(void*))
{
    long i;

    if (queue == NULL)
        return;

    for (i = 0; i < queue->len; i++) {
        if (item_destroy != NULL && queue->tab[i]->item != NULL)
            item_destroy(queue->tab[i]->item);
        gw_free(queue->tab[i]);
    }
    mutex_destroy(queue->mutex);
    pthread_cond_destroy(&queue->nonempty);
    gw_free(queue->tab);
    gw_free(queue);
}
