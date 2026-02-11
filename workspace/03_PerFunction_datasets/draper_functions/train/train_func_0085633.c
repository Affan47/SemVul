sring_read_string(sring_buffer *buf)
{
	int n;
	char *border;
	char *p;
	char *dst;
	int dst_len;

	if (buf == NULL)
		return NULL;

	n = sring_getMaxRead(buf);
	border = buf->data + buf->size;
	p = buf->data + buf->r;

	while (--n >= 0) {
		if (*p == '\r' || *p == '\n' || *p == '\0')
			break;
		p++;
		if (p == border)
			p = buf->data;
	};

	if (n == -1)
		return NULL;

	dst_len = sring_getMaxRead(buf) - n;
	if ((dst = malloc(dst_len)) == NULL)
		return NULL;

	sring_read(buf, dst, dst_len);
	dst[dst_len-1] = '\0';

	return dst;
}
