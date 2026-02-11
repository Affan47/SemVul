rc_input_close(rc_input_t *r) {
	if (!r)
		return;

	debug_function("[rc] closing (0x%x) fd: %d path:%s\n", r, r->fd, r->path);

	if (r->type == RC_INPUT_PIPE)
		unlink(r->path);

	if (r->fd != -1) {
		watch_t *w = rc_watch_find(r->fd);

		if (w) {
			if (w->data == r)
				debug_function("[rc] rc_input_close() watch 0x%x OK\n", r);
			else	debug_error("[rc] rc_input_close() watch: 0x%x r: 0x%x\n", w->data, r);

			w->data = NULL;
			watch_free(w);
		}


		close(r->fd);
		r->fd = -1;
	}

	xfree(r->path);
	list_remove(&rc_inputs, r, 1);
}
