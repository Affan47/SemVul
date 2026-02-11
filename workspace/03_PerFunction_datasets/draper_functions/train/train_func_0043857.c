dir_delete(struct dir_queue_t *queue, fcb *to_delete)
{

    if (queue->head == null && queue->tail == null) {

        error_file.error = ERROR_DIR_QUEUE_EMPTY;
        return &error_file;
    }


    if (to_delete == null){
        error_file.error = ERROR_BAD_FILE_PTR;
        return &error_file;
    }
    fcb *ret = to_delete;

    if(to_delete->next == null && to_delete->prev == null){
        queue->head = null;
        queue->tail = null;
    }

    else if(to_delete->prev == null){
        queue->tail = to_delete->next;
        queue->tail->prev = null;
    }

    else if(to_delete->next == null){
        queue->head = to_delete->prev;
        queue->head->next = null;
    }

    else{
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
    }

    queue->size--;
    return (ret);
}
