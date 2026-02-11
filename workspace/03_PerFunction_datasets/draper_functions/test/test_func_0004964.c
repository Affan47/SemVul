ekg_write(int fd, const char *buf, int len) {
	watch_t *wl = NULL;
	list_t l;

	if (fd == -1)
		return -1;


	for (l = watches; l; l = l->next) {
		watch_t *w = l->data;

		if (w && w->fd == fd && w->type == WATCH_WRITE && w->buf) {
			wl = w;
			break;
		}
	}

	if (wl) {
		if (!buf && len == -1)
			return wl->buf->len;
	} else {

		wl = watch_add(NULL, fd, WATCH_WRITE_LINE, NULL, NULL);
	}

	return watch_write_data(wl, buf, len);
}
