fwdStartPeer(peer * p, StoreEntry * e, request_t * r)
{
    FwdState *fwdState;
    FwdServer *peer = NULL;
    debug(17, 3) ("fwdStartPeer: '%s'\n", storeUrl(e));
    e->mem_obj->request = requestLink(r);
#if URL_CHECKSUM_DEBUG
    assert(e->mem_obj->chksum == url_checksum(e->mem_obj->url));
#endif
    fwdState = cbdataAlloc(FwdState);
    fwdState->entry = e;
    fwdState->client_fd = -1;
    fwdState->server_fd = -1;
    fwdState->request = requestLink(r);
    fwdState->start = squid_curtime;
    fwdState->orig_entry_flags = e->flags;
    storeLockObject(e);
    if (!fwdState->request->flags.pinned)
	EBIT_SET(e->flags, ENTRY_FWD_HDR_WAIT);
    storeRegisterAbort(e, fwdAbort, fwdState);
    peerAddFwdServer(&peer, p, HIER_DIRECT);
    fwdStartComplete(peer, fwdState);
}
