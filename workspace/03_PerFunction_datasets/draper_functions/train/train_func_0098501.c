fs_queue_push_head_link(fs_queue *queue, fs_list *link) {
    if (queue == NULL || link == NULL) {
        return;
    }
    if (link->prev != NULL || link->next != NULL) {
        return;
    }
    link->next = queue->head;
    if (queue->head)
        queue->head->prev = link;
    else
        queue->tail = link;
    queue->head = link;
    queue->length++;
}
