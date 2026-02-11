delete_handler(int fd, short which, void *arg) {
    struct timeval t;
    static int initialized = 0;

    if (initialized) {


        evtimer_del(&deleteevent);
    } else {
        initialized = 1;
    }

    evtimer_set(&deleteevent, delete_handler, 0);
    t.tv_sec = 5; t.tv_usec=0;
    evtimer_add(&deleteevent, &t);

    {
        int i, j=0;
        time_t now = time(0);
        for (i=0; i<delcurr; i++) {
            item *it = todelete[i];
            if (it->exptime <= now) {
                assert(it->refcount > 0);
                it->it_flags &= ~ITEM_DELETED;
                item_unlink(it);
                item_remove(it);
            } else {
                todelete[j++] = it;
            }
        }
        delcurr = j;
    }

    return;
}
