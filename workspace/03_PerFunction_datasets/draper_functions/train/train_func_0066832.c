stalloc(size_t nbytes)
{
	char *p;
	size_t aligned;

	aligned = SHELL_ALIGN(nbytes);
	if (aligned > g_stacknleft) {
		size_t len;
		size_t blocksize;
		struct stack_block *sp;

		blocksize = aligned;
		if (blocksize < MINSIZE)
			blocksize = MINSIZE;
		len = sizeof(struct stack_block) - MINSIZE + blocksize;
		if (len < blocksize)
			ash_msg_and_raise_error(bb_msg_memory_exhausted);
		INT_OFF;
		sp = ckmalloc(len);
		sp->prev = g_stackp;
		g_stacknxt = sp->space;
		g_stacknleft = blocksize;
		sstrend = g_stacknxt + blocksize;
		g_stackp = sp;
		INT_ON;
	}
	p = g_stacknxt;
	g_stacknxt += aligned;
	g_stacknleft -= aligned;
	return p;
}
