storeAbort(StoreEntry * e)
{
    MemObject *mem = e->mem_obj;
    assert(e->store_status == STORE_PENDING);
    assert(mem != NULL);
    debug(20, 6) ("storeAbort: %s\n", storeKeyText(e->hash.key));
    storeLockObject(e);
    storeExpireNow(e);
    storeReleaseRequest(e);
    EBIT_SET(e->flags, ENTRY_ABORTED);
    storeSetMemStatus(e, NOT_IN_MEMORY);
    e->store_status = STORE_OK;


    mem->object_sz = mem->inmem_hi;

    if (mem->abort.callback) {
	eventAdd("mem->abort.callback",
	    mem->abort.callback,
	    mem->abort.data,
	    0.0,
	    0);
	mem->abort.callback = NULL;
	mem->abort.data = NULL;
    }

    InvokeHandlers(e);

    storeSwapOutFileClose(e);
    storeUnlockObject(e);
}
