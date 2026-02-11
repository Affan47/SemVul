flushout(struct output *dest)
{
#ifdef USE_GLIBC_STDIO
	INTOFF;
	fflush(dest->stream);
	INTON;
#else
	size_t len;

	len = dest->nextc - dest->buf;
	if (!len || dest->fd < 0)
		return;
	dest->nextc = dest->buf;
	if ((xwrite(dest->fd, dest->buf, len)))
		dest->flags |= OUTPUT_ERR;
#endif
}
