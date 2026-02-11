do_item_flush_expired(void) {
    int i;
    item *iter, *next;
    if (settings.oldest_live == 0)
        return;
    for (i = 0; i < LARGEST_ID; i++) {


        for (iter = heads[i]; iter != NULL; iter = next) {
            if (iter->time >= settings.oldest_live) {
                next = iter->next;
                if ((iter->it_flags & ITEM_SLABBED) == 0) {
                    do_item_unlink(iter);
                }
            } else {

                break;
            }
        }
    }
}
