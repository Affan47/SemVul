init_listeners(struct Listener_head *listeners, const struct Table_head *tables) {
    struct Listener *iter;
    int count = 0;

    SLIST_FOREACH(iter, listeners, entries) {
        if (init_listener(iter, tables) <= 0) {
            fprintf(stderr, "Failed to initalize listener: \n");
            print_listener_config(stderr, iter);
            return -1;
        }
        count ++;
    }

    return count;
}
