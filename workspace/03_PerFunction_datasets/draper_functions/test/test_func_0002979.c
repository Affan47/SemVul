comm_write(int fd, const char *buf, int size, CWCB * handler, void *handler_data, FREE * free_func)
{
    CommWriteStateData *state = &fd_table[fd].rwstate;
    debug(5, 5) ("comm_write: FD %d: sz %d: hndl %p: data %p.\n",
	fd, size, handler, handler_data);
    if (state->valid) {
	debug(5, 1) ("comm_write: fd_table[%d].rwstate.valid == true!\n", fd);
	fd_table[fd].rwstate.valid = 0;
#if DELAY_POOLS

	assert(state->write_delayed == 0);
#endif
    }
    state->buf = (char *) buf;
    state->size = size;
    state->header_size = 0;
    state->offset = 0;
    state->handler = handler;
    state->handler_data = handler_data;
    state->free_func = free_func;
    state->valid = 1;
#if DELAY_POOLS
    state->delayid = 0;
    state->write_delayed = 0;
#endif
    cbdataLock(handler_data);
    commSetSelect(fd, COMM_SELECT_WRITE, commHandleWrite, NULL, 0);
}
