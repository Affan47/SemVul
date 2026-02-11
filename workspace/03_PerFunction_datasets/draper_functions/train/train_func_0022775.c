fs_queue_peek_nth_link(fs_queue *queue, unsigned int n) {
    fs_list *link;
    int i;

    if (queue == NULL) {
        return NULL;
    }

    if (n >= queue->length)
        return NULL ;

    if (n > queue->length / 2) {
        n = queue->length - n - 1;

        link = queue->tail;
        for (i = 0; i < n; ++i)
            link = link->prev;
    } else {
        link = queue->head;
        for (i = 0; i < n; ++i)
            link = link->next;
    }

    return link;
}
