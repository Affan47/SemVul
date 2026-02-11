grow_read_buffer (urlinfo *u, size_t bgot)
{
    size_t newlen = 2 * u->buflen;
    char *newbuf;

    while (newlen < u->datalen + bgot) {
	newlen *= 2;
    }

    newbuf = realloc(u->getbuf, newlen);

    if (newbuf == NULL) {
	return E_ALLOC;
    } else {
	size_t addlen = newlen - u->buflen;


	memset(newbuf + u->datalen, 0, addlen);
	u->getbuf = newbuf;
	u->buflen = newlen;
	return 0;
    }
}
