buffer_put(Buffer *buf, const void *data, size_t len) {
	if (!buffer_alloc(buf, len))
		return false;
	memcpy(buf->data, data, len);
	buf->len = len;
	return true;
}
