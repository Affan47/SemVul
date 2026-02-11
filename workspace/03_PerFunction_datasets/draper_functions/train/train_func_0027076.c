channel_close_listener(Channel * c) {
    LINK list;
    LINK * list_next = NULL;

    list_init(&list);
    for (list_next = file_info_ring.next; list_next != &file_info_ring; list_next = list_next->next) {
        OpenFileInfo * h = ring2file(list_next);
        if (h->inp == &c->inp) {
            trace(LOG_ALWAYS, "file handle left open by client: FS%d", h->handle);
            list_remove(&h->link_hash);
            if (h->dir != NULL) {
                closedir(h->dir);
                h->dir = NULL;
            }
            if (h->file >= 0) {
                int posted = 0;
                while (!list_is_empty(&h->link_reqs)) {
                    LINK * link = h->link_reqs.next;
                    IORequest * req = reqs2req(link);
                    list_remove(link);
                    if (h->posted_req == req) {
                        req->handle = NULL;
                        posted = 1;
                    }
                    else {
                        loc_free(req->info.u.fio.bufp);
                        loc_free(req);
                    }
                }
                if (!posted) close(h->file);
            }
            list_add_last(&h->link_hash, &list);
        }
    }

    while (!list_is_empty(&list)) delete_open_file_info(hash2file(list.next));
}
