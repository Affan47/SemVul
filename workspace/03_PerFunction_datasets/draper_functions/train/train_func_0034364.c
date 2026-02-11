axio_init(int in, int out, int paclen, char *eol)
{
	ax25io *new;

	if ((new = calloc(1, sizeof(ax25io))) == NULL)
		return NULL;

	if (paclen > AXBUFLEN)
		paclen = AXBUFLEN;

	new->ifd = in;
	new->ofd = out;
	new->eolmode = EOLMODE_TEXT;
	new->paclen = paclen;
	new->gbuf_usage = 0;

	strncpy(new->eol, eol, 3);
	new->eol[3] = 0;

	new->next = Iolist;
	Iolist = new;

	return new;
}
