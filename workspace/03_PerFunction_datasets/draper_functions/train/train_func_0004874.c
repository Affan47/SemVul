pgetb(P *p)
{
	unsigned char c;

	if (p->ofst == GSIZE(p->hdr))
		return NO_MORE_DATA;
	c = GCHAR(p);
	if (++p->ofst == GSIZE(p->hdr))
		pnext(p);
	++p->byte;
	if (c == '\n') {
		++(p->line);
		p->col = 0;
		p->valcol = 1;
	} else if (p->b->o.crlf && c == '\r') {
		if (brc(p) == '\n')
			return pgetb(p);
		else
			p->valcol = 0;
	} else {
		p->valcol = 0;
	}
	return c;
}
