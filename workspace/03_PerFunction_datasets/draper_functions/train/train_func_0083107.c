gopherReadReply(int fd, void *data)
{
    GopherStateData *gopherState = data;
    StoreEntry *entry = gopherState->entry;
    char *buf = NULL;
    int len;
    int clen;
    int bin;
    size_t read_sz;
#if DELAY_POOLS
    delay_id delay_id;
#endif
    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
	comm_close(fd);
	return;
    }
    errno = 0;
    buf = memAllocate(MEM_4K_BUF);
    read_sz = 4096 - 1;
#if DELAY_POOLS
    delay_id = delayMostBytesAllowed(entry->mem_obj, &read_sz);
#endif

    statCounter.syscalls.sock.reads++;
    len = FD_READ_METHOD(fd, buf, read_sz);
    if (len > 0) {
	fd_bytes(fd, len, FD_READ);
#if DELAY_POOLS
	delayBytesIn(delay_id, len);
#endif
	kb_incr(&statCounter.server.all.kbytes_in, len);
	kb_incr(&statCounter.server.other.kbytes_in, len);
    }
    debug(10, 5) ("gopherReadReply: FD %d read len=%d\n", fd, len);
    if (len > 0) {
	commSetTimeout(fd, Config.Timeout.read, NULL, NULL);
	IOStats.Gopher.reads++;
	for (clen = len - 1, bin = 0; clen; bin++)
	    clen >>= 1;
	IOStats.Gopher.read_hist[bin]++;
    }
    if (len < 0) {
	debug(50, 1) ("gopherReadReply: error reading: %s\n", xstrerror());
	if (ignoreErrno(errno)) {
	    commSetSelect(fd, COMM_SELECT_READ, gopherReadReply, data, 0);
	} else {
	    ErrorState *err;
	    err = errorCon(ERR_READ_ERROR, HTTP_BAD_GATEWAY, gopherState->fwdState->request);
	    err->xerrno = errno;
	    fwdFail(gopherState->fwdState, err);
	    comm_close(fd);
	}
    } else if (len == 0 && entry->mem_obj->inmem_hi == 0) {
	fwdFail(gopherState->fwdState, errorCon(ERR_ZERO_SIZE_OBJECT, HTTP_BAD_GATEWAY, gopherState->fwdState->request));
	comm_close(fd);
    } else if (len == 0) {


	if (gopherState->conversion != NORMAL)
	    gopherEndHTML(data);
	storeTimestampsSet(entry);
	storeBufferFlush(entry);
	fwdComplete(gopherState->fwdState);
	comm_close(fd);
    } else {
	if (gopherState->conversion != NORMAL) {
	    gopherToHTML(data, buf, len);
	} else {
	    storeAppend(entry, buf, len);
	}
	commSetSelect(fd,
	    COMM_SELECT_READ,
	    gopherReadReply,
	    data, 0);
    }
    memFree(buf, MEM_4K_BUF);
    return;
}
