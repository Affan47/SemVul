class1(graph_t * g)
{
    node_t *n, *t, *h;
    edge_t *e, *rep;

    mark_clusters(g);
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	for (e = agfstout(g, n); e; e = agnxtout(g, e)) {


	    if (ED_to_virt(e))
		continue;


	    if (nonconstraint_edge(e))
		continue;

	    t = UF_find(agtail(e));
	    h = UF_find(aghead(e));


	    if (t == h)
		continue;


	    if (ND_clust(t) || ND_clust(h)) {
		interclust1(g, agtail(e), aghead(e), e);
		continue;
	    }

	    if ((rep = find_fast_edge(t, h)))
		merge_oneway(e, rep);
	    else
		virtual_edge(t, h, e);

#ifdef NOTDEF
	    if ((t == agtail(e)) && (h == aghead(e))) {
		if (rep = find_fast_edge(t, h))
		    merge_oneway(e, rep);
		else
		    virtual_edge(t, h, e);
	    } else {
		f = agfindedge(g, t, h);
		if (f && (ED_to_virt(f) == NULL))
		    rep = virtual_edge(t, h, f);
		else
		    rep = find_fast_edge(t, h);
		if (rep)
		    merge_oneway(e, rep);
		else
		    virtual_edge(t, h, e);
	    }
#endif
	}
    }
}
