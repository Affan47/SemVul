lalloc(int used)
{
    register LINE   *lp;
    register int    size;
    EML             eml;

    if((size = (used+NBLOCK-1) & ~(NBLOCK-1)) > NLINE)
      size *= 2;

    if (size == 0)
      size = NBLOCK;

    if ((lp = (LINE *) malloc(sizeof(LINE)+(size*sizeof(CELL)))) == NULL) {
	eml.s = comatose(size);
	emlwrite("Cannot allocate %s bytes", &eml);
	return (NULL);
    }

    lp->l_size = size;
    lp->l_used = used;
    return (lp);
}
