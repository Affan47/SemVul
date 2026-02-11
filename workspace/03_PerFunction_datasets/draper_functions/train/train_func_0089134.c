nextchar(char * p) {
    if (p) {
	p++;
	if (opts & aeLONGCOND) {

    	    if (p == c.l.conds1 + MAXCONDLEN_1) return c.l.conds2;

	} else if (p == c.conds + MAXCONDLEN) return NULL;
	return *p ? p : NULL;
    }
    return NULL;
}
