gigaset_isoc_input(struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;
	unsigned tail, head, numbytes;
	unsigned char *src;

	head = inbuf->head;
	while (head != (tail = inbuf->tail)) {
		gig_dbg(DEBUG_INTR, "buffer state: %u -> %u", head, tail);
		if (head > tail)
			tail = RBUFSIZE;
		src = inbuf->data + head;
		numbytes = tail - head;
		gig_dbg(DEBUG_INTR, "processing %u bytes", numbytes);

		if (cs->mstate == MS_LOCKED) {
			gigaset_dbg_buffer(DEBUG_LOCKCMD, "received response",
					   numbytes, src);
			gigaset_if_receive(inbuf->cs, src, numbytes);
		} else {
			cmd_loop(src, numbytes, inbuf);
		}

		head += numbytes;
		if (head == RBUFSIZE)
			head = 0;
		gig_dbg(DEBUG_INTR, "setting head to %u", head);
		inbuf->head = head;
	}
}
