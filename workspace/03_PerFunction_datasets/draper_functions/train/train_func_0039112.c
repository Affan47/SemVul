buffer_free(Buffer *buf) {
	if (!buf)
		return;
	free(buf->data);
	buf->data = NULL;
	buf->len = 0;
	buf->size = 0;
}
