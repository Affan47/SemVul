gopherStart(FwdState * fwdState)
{
    int fd = fwdState->server_fd;
    StoreEntry *entry = fwdState->entry;
    GopherStateData *gopherState;
    CBDATA_INIT_TYPE(GopherStateData);
    gopherState = cbdataAlloc(GopherStateData);
    gopherState->buf = memAllocate(MEM_4K_BUF);
    storeLockObject(entry);
    gopherState->entry = entry;
    gopherState->fwdState = fwdState;
    debug(10, 3) ("gopherStart: %s\n", storeUrl(entry));
    statCounter.server.all.requests++;
    statCounter.server.other.requests++;

    gopher_request_parse(fwdState->request,
	&gopherState->type_id, gopherState->request);
    comm_add_close_handler(fd, gopherStateFree, gopherState);
    if (((gopherState->type_id == GOPHER_INDEX) || (gopherState->type_id == GOPHER_CSO))
	&& (strchr(gopherState->request, '?') == NULL)) {


	gopherMimeCreate(gopherState);
	if (gopherState->type_id == GOPHER_INDEX) {
	    gopherState->conversion = HTML_INDEX_PAGE;
	} else {
	    if (gopherState->type_id == GOPHER_CSO) {
		gopherState->conversion = HTML_CSO_PAGE;
	    } else {
		gopherState->conversion = HTML_INDEX_PAGE;
	    }
	}
	gopherToHTML(gopherState, (char *) NULL, 0);
	fwdComplete(fwdState);
	comm_close(fd);
	return;
    }
    gopherState->fd = fd;
    gopherState->fwdState = fwdState;
    commSetSelect(fd, COMM_SELECT_WRITE, gopherSendRequest, gopherState, 0);
    commSetTimeout(fd, Config.Timeout.read, gopherTimeout, gopherState);
}
