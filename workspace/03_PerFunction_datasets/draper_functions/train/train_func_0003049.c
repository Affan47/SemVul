net_buf_alloc(struct net_buf_t * buf)
{
	if (!buf) {
		return -EINVAL;
	}

	buf->len = buf->off;
	buf->off = 0;
	buf->ptr = calloc(1, buf->len + 1);

	if (!buf->ptr) {
		return -ENOMEM;
	}

	return 0;
}
