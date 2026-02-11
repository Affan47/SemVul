count_all_crossings(nodelist_t * list, Agraph_t * subg)
{
    nodelistitem_t *item;
    edgelist *openEdgeList = init_edgelist();
    Agnode_t *n;
    Agedge_t *e;
    int crossings = 0;
    int order = 1;

    for (n = agfstnode(subg); n; n = agnxtnode(subg, n)) {
	for (e = agfstout(subg, n); e; e = agnxtout(subg, e)) {
	    EDGEORDER(e) = 0;
	}
    }

    for (item = list->first; item; item = item->next) {
	n = item->curr;

	for (e = agfstedge(subg, n); e; e = agnxtedge(subg, e, n)) {
	    if (EDGEORDER(e) > 0) {
		edgelistitem *eitem;
		Agedge_t *ep;

		for (eitem = (edgelistitem *) dtfirst(openEdgeList); eitem;
		     eitem =
		     (edgelistitem *) dtnext(openEdgeList, eitem)) {
		    ep = eitem->edge;
		    if (EDGEORDER(ep) > EDGEORDER(e)) {
			if ((aghead(ep) != n) && (agtail(ep) != n))
			    crossings++;
		    }
		}
		remove_edge(openEdgeList, e);
	    }
	}

	for (e = agfstedge(subg, n); e; e = agnxtedge(subg, e, n)) {
	    if (EDGEORDER(e) == 0) {
		EDGEORDER(e) = order;
		add_edge(openEdgeList, e);
	    }
	}
	order++;
    }

    free_edgelist(openEdgeList);
    return crossings;
}
