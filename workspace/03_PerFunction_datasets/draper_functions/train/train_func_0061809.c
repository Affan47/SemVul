uih_setincoloringmode(uih_context * c, int mode)
{
    if (mode < 0)
	mode = rand() % INCOLORING;
    if (mode > INCOLORING)
	mode = INCOLORING;
    if (c->fcontext->incoloringmode != mode) {
	char str[10];
	c->fcontext->incoloringmode = mode;
	c->fcontext->version++;
	uih_newimage(c);
	sprintf(str, "in%i", mode);
	uih_updatemenus(c, str);
    }
}
