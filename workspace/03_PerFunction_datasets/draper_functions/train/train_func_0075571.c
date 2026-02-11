dir_init_queue(struct dir_queue_t *queue) {
    fcb *temp;
    fcb *tempnext;

    temp = queue->tail;
    while (temp != null) {
        tempnext = temp->next;
        Free(temp);
        temp = tempnext;
    }

    queue->head = null;
    queue->tail = null;
    queue->size = 0;
    queue->initialized = 1;
}
