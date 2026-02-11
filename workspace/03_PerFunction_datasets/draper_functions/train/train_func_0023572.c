skipblank(struct uih_context *uih)
{
    int c;
    if (uih->playstring != NULL) {
	while ((uih->playstring[uih->playpos] == ' ' ||
		uih->playstring[uih->playpos] == '\t' ||
		uih->playstring[uih->playpos] == '\r' ||
		uih->playstring[uih->playpos] == '\n'))
	    uih->playpos++;
	return;
    }
    do {
	c = xio_getc(FD);
	if (c == '\n')
	    uih->playc->line++;
	if (c == ';')
	    while (c != '\n' && !xio_feof(FD)) {
		c = xio_getc(FD);
		if (c == '\n')
		    uih->playc->line++;
	    }
	while (xio_feof(FD) && uih->playc->level) {
	    c = XIO_EOF + 1;
	    xio_close(FD);
	    uih->playc->file = uih->playc->prevfiles[--uih->playc->level];
	    uih->playc->line = 1;
	}
    }
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r'
	   || c == XIO_EOF + 1);
    if (c != XIO_EOF)
	xio_ungetc(c, FD);
}
