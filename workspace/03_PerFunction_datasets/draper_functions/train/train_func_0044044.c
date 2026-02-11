free_connections() {
    struct Connection *iter;

    while ((iter = LIST_FIRST(&connections)) != NULL) {
        LIST_REMOVE(iter, entries);
        free_connection(iter);
    }
}
