free_listeners(struct Listener_head *listeners) {
    struct Listener *iter;

    while ((iter = SLIST_FIRST(listeners)) != NULL) {
        SLIST_REMOVE_HEAD(listeners, entries);
        close_listener(iter);
        free_listener(iter);
    }
}
