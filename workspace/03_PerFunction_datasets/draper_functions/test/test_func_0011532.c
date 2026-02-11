ll_lcdlist_destroy(g15daemon_t **masterlist) {
    int i = 0;

    while ((*masterlist)->head != (*masterlist)->tail) {
        i++;
        g15daemon_lcdnode_remove((*masterlist)->head);
    }

    free((*masterlist)->tail->lcd);
    free((*masterlist)->tail);
    free(*masterlist);

    pthread_mutex_destroy(&lcdlist_mutex);
}
