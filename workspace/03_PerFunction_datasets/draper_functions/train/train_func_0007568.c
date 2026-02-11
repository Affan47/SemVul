fifo_pull(SCREEN *sp)
{
    int ch;
    ch = sp->_fifo[head];
    TR(TRACE_IEVENT, ("pulling %s from %d", _nc_tracechar(sp, ch), head));

    if (peek == head) {
	h_inc();
	peek = head;
    } else
	h_inc();

#ifdef TRACE
    if (USE_TRACEF(TRACE_IEVENT)) {
	_nc_fifo_dump(sp);
	_nc_unlock_global(tracef);
    }
#endif
    return ch;
}
