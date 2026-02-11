ne_lock_using_resource(ne_request *req, const char *uri, int depth)
{
    struct lh_req_cookie *lrc = ne_get_request_private(req, HOOK_ID);
    struct lock_list *item;
    int match;

    if (lrc == NULL)
	return;


    for (item = lrc->store->locks; item != NULL; item = item->next) {

	match = 0;

	if (depth == NE_DEPTH_INFINITE &&
	    ne_path_childof(uri, item->lock->uri.path)) {


	    NE_DEBUG(NE_DBG_LOCKS, "Has child: %s\n", item->lock->token);
	    match = 1;
	}
	else if (ne_path_compare(uri, item->lock->uri.path) == 0) {

	    NE_DEBUG(NE_DBG_LOCKS, "Has direct lock: %s\n", item->lock->token);
	    match = 1;
	}
	else if (item->lock->depth == NE_DEPTH_INFINITE &&
		 ne_path_childof(item->lock->uri.path, uri)) {


	    NE_DEBUG(NE_DBG_LOCKS, "Is child of: %s\n", item->lock->token);
	    match = 1;
	}

	if (match) {
	    submit_lock(lrc, item->lock);
	}
    }

}
