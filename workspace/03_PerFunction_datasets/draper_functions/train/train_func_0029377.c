gfarm_iobuffer_read(struct gfarm_iobuffer *b, int *residualp)
{
	int space, rv;

	if (IOBUFFER_IS_FULL(b))
		return;

	space = b->head + (b->bufsize - b->tail);
	if (residualp == NULL)
		residualp = &space;
	if (*residualp <= 0)
		return;
	if (*residualp > b->bufsize - b->tail && b->head > 0) {
		memmove(b->buffer, b->buffer + b->head,
			IOBUFFER_AVAIL_LENGTH(b));
		b->tail -= b->head;
		b->head = 0;
	}

	rv = (*b->read_func)(b, b->read_cookie, b->read_fd,
			     b->buffer + b->tail,
			     *residualp < space ? *residualp : space);
	if (rv == 0) {
		b->read_eof = 1;
	} else if (rv > 0) {
		b->tail += rv;
		*residualp -= rv;
	}
	return;
}
