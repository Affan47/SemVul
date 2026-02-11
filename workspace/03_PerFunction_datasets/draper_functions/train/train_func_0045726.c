buffer_append(Buffer *buf, const void *data, size_t len) {
	size_t rem = buf->size - buf->len;
	if (len > rem && !buffer_alloc(buf, buf->size + len - rem))
		return false;
	memcpy(buf->data + buf->len, data, len);
	buf->len += len;
	return true;
}
