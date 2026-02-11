pack_window_close(struct pack_window **w_cursor)
{
	struct pack_window *w = *w_cursor;
	if (w) {
		w->inuse_cnt--;
		*w_cursor = NULL;
	}
}
