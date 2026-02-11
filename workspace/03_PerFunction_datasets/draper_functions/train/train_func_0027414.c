fs_queue_delete_link(fs_queue *queue, fs_list *link_) {
    if (queue == NULL || link_ == NULL) {
        return;
    }
    fs_queue_unlink(queue, link_);
    fs_list_free(link_);
}
