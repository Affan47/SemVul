checkChain(graph_t * g)
{
    node_t *t;
    node_t *h;
    edge_t *e;
    t = GD_nlist(g);
    for (h = ND_next(t); h; h = ND_next(h)) {
	if (!agfindedge(g, t, h)) {
	    e = agedge(g, t, h, NULL, 1);
	    agbindrec(e, "Agedgeinfo_t", sizeof(Agedgeinfo_t), TRUE);
	    ED_minlen(e) = 0;
	    elist_append(e, ND_out(t));
	    elist_append(e, ND_in(h));
	}
	t = h;
    }
}
