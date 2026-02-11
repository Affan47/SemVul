scc_add_to_readbufv(int port, double dcycs, const char *fmt, ...)
{
	va_list	ap;
	char	*bufptr;
	int	ret, len, c;
	int	i;

	va_start(ap, fmt);
	bufptr = malloc(4096);
	bufptr[0] = 0;
	ret = vsnprintf(bufptr, 4090, fmt, ap);
	len = strlen(bufptr);
	for(i = 0; i < len; i++) {
		c = bufptr[i];
		if(c == 0x0a) {
			scc_add_to_readbuf(port, 0x0d, dcycs);
		}
		scc_add_to_readbuf(port, c, dcycs);
	}
	va_end(ap);
}
