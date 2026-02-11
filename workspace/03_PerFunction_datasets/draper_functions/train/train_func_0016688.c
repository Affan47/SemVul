set_attrwf(Agraph_t * g, int toplevel, int value)
{
    Agraph_t *subg;
    Agnode_t *n;
    Agedge_t *e;

    AGATTRWF(g) = value;
    for (subg = agfstsubg(g); subg; subg = agnxtsubg(subg)) {
	set_attrwf(subg, FALSE, value);
    }
    if (toplevel) {
	for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	    AGATTRWF(n) = value;
	    for (e = agfstout(g, n); e; e = agnxtout(g, e))
		AGATTRWF(e) = value;
	}
    }
}
