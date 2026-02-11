buf_setmap(struct buf *buf, const char *base, unsigned len)
{
    buf_reset(buf);
    if (len) {
	buf_ensure(buf, len);
	memcpy(buf->s, base, len);
	buf->len = len;
    }
}
