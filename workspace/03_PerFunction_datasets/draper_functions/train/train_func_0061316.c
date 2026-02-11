write_edge_name(Agedge_t * e, iochan_t * ofile, int terminate)
{
    int rv;
    char *p;
    Agraph_t *g;

    p = agnameof(e);
    g = agraphof(e);
    if (NOT(EMPTY(p))) {
	CHKRV(ioput(g, ofile, " [key="));
	CHKRV(write_canonstr(g, ofile, p));
	if (terminate)
	    CHKRV(ioput(g, ofile, "]"));
	rv = TRUE;
    } else
	rv = FALSE;
    return rv;
}
