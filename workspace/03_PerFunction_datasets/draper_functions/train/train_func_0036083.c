kill_redundant_list(Prefetch_array_data *list)
{
    Prefetch_array_data *pad;
    if (!list)
        return;
    for (pad = list; pad != NULL; pad = pad->next) {
        Prefetch_array_data *d;
        for (d = pad->next; d != NULL; d = d->next) {
            if (is_same_cache_line(pad, d)) {
                if (d->prev) {
                    d->prev->next = d->next;
                    if (d->next) {
                        d->next->prev = d->prev;
                    }
                } else {
                    list = d->next;
                    list->prev = NULL;
                }
                free(d);
            }
        }
    }
}
