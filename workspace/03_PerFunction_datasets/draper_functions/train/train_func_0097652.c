has_input(struct mansession *s)
{
	int x;
	for (x=1;x<s->inlen;x++)
		if ((s->inbuf[x] == '\n') && (s->inbuf[x-1] == '\r'))
			return 1;
	return 0;
}
