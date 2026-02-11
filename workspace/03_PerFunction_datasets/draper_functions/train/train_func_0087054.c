receive_translation(AyConnection *fd, eb_input_condition cond,
	void *data)
{
	struct http_data *d = data;
	int len = 0;

	while ((len = ay_connection_read(fd, d->buf+d->len, sizeof(d->buf) - d->len)) > 0) {
		char *end, *start;

		start = strstr(d->buf, START_POS);

		if (!start)
			continue;

		d->len += len;

		d->buf[len] = '\0';
		trim_start(d->buf, start - d->buf, d->len);
		d->len -= start - d->buf;

		end = strstr(d->buf, END_POS);
		if (end) {
			*end = '\0';
			d->done = 1;
			trim_start(d->buf, strlen(START_POS), d->len);
			ay_connection_input_remove(d->handle);
			return;
		}
	}

	if (len ==0 || (len < 0 && errno != EAGAIN)) {
		d->error = 1;
		d->done = 1;
		ay_connection_input_remove(d->handle);
	}
}
