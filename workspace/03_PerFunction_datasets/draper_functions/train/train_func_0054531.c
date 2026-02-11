gigaset_fill_inbuf(struct inbuf_t *inbuf, const unsigned char *src,
		       unsigned numbytes)
{
	unsigned n, head, tail, bytesleft;

	gig_dbg(DEBUG_INTR, "received %u bytes", numbytes);

	if (!numbytes)
		return 0;

	bytesleft = numbytes;
	tail = inbuf->tail;
	head = inbuf->head;
	gig_dbg(DEBUG_INTR, "buffer state: %u -> %u", head, tail);

	while (bytesleft) {
		if (head > tail)
			n = head - 1 - tail;
		else if (head == 0)
			n = (RBUFSIZE - 1) - tail;
		else
			n = RBUFSIZE - tail;
		if (!n) {
			dev_err(inbuf->cs->dev,
				"buffer overflow (%u bytes lost)\n",
				bytesleft);
			break;
		}
		if (n > bytesleft)
			n = bytesleft;
		memcpy(inbuf->data + tail, src, n);
		bytesleft -= n;
		tail = (tail + n) % RBUFSIZE;
		src += n;
	}
	gig_dbg(DEBUG_INTR, "setting tail to %u", tail);
	inbuf->tail = tail;
	return numbytes != bytesleft;
}
