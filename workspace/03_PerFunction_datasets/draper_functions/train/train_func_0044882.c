stats_prefix_clear() {
    int i;

    for (i = 0; i < PREFIX_HASH_SIZE; i++) {
        PREFIX_STATS *cur, *next;
        for (cur = prefix_stats[i]; cur != NULL; cur = next) {
            next = cur->next;
            free(cur->prefix);
            free(cur);
        }
        prefix_stats[i] = NULL;
    }
    num_prefixes = 0;
    total_prefix_size = 0;
}
