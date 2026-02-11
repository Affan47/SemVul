storeClientCopyPending(store_client * sc, StoreEntry * e, void *data)
{
#if STORE_CLIENT_LIST_DEBUG
    assert(sc == storeClientListSearch(e->mem_obj, data));
#endif
    assert(sc->entry == e);
    if (sc == NULL)
	return 0;
    if (sc->new_callback == NULL)
	return 0;
    return 1;
}
