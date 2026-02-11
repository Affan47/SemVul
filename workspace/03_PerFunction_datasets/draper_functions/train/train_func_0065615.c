storeCreateEntry(const char *url, request_flags flags, method_t * method)
{
    StoreEntry *e = NULL;
    MemObject *mem = NULL;
    debug(20, 3) ("storeCreateEntry: '%s'\n", url);

    e = new_StoreEntry(STORE_ENTRY_WITH_MEMOBJ, url);
    e->lock_count = 1;
    mem = e->mem_obj;
    mem->method = urlMethodDup(method);
    if (neighbors_do_private_keys || !flags.hierarchical)
	storeSetPrivateKey(e);
    else
	storeSetPublicKey(e);
    if (flags.cachable) {
	EBIT_SET(e->flags, ENTRY_CACHABLE);
	EBIT_CLR(e->flags, RELEASE_REQUEST);
    } else {
	EBIT_CLR(e->flags, ENTRY_CACHABLE);
	storeReleaseRequest(e);
    }
    e->store_status = STORE_PENDING;
    storeSetMemStatus(e, NOT_IN_MEMORY);
    e->swap_status = SWAPOUT_NONE;
    e->swap_filen = -1;
    e->swap_dirn = -1;
    e->refcount = 0;
    e->lastref = squid_curtime;
    e->timestamp = -1;
    e->ping_status = PING_NONE;
    EBIT_SET(e->flags, ENTRY_VALIDATED);
    return e;
}
