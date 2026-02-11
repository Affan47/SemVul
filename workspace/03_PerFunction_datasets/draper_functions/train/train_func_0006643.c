treeupdate(node_t * v, node_t * w, int cutvalue, int dir)
{
    edge_t *e;
    int d;

    while (!SEQ(ND_low(v), ND_lim(w), ND_lim(v))) {
	e = ND_par(v);
	if (v == agtail(e))
	    d = dir;
	else
	    d = NOT(dir);
	if (d)
	    ED_cutvalue(e) += cutvalue;
	else
	    ED_cutvalue(e) -= cutvalue;
	if (ND_lim(agtail(e)) > ND_lim(aghead(e)))
	    v = agtail(e);
	else
	    v = aghead(e);
    }
    return v;
}
