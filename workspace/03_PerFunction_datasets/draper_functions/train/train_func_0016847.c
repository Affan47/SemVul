upperregion(int f, int n)
{
    register LINE   *linep;
    register int    loffs;
    register int    c;
    register int    s;
    REGION          region;
    CELL            ac;

    ac.a = 0;
    if (curbp->b_mode&MDVIEW)
      return(rdonly());

    if ((s=getregion(&region, curwp->w_markp, curwp->w_marko)) != TRUE)
      return (s);

    lchange(WFHARD);
    linep = region.r_linep;
    loffs = region.r_offset;
    while (region.r_size--) {
	if (loffs == llength(linep)) {
	    linep = lforw(linep);
	    loffs = 0;
	} else {
	    c = lgetc(linep, loffs).c;
	    if (c>='a' && c<='z'){
		ac.c = c - 'a' + 'A';
		lputc(linep, loffs, ac);
	    }
	    ++loffs;
	}
    }

    return (TRUE);
}
