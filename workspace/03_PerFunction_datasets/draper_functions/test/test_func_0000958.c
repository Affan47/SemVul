emit_view(GVJ_t * job, graph_t * g, int flags)
{
    GVC_t * gvc = job->gvc;
    node_t *n;
    edge_t *e;

    gvc->common.viewNum++;

    if (!(flags & EMIT_CLUSTERS_LAST))
	emit_clusters(job, g, flags);
    if (flags & EMIT_SORTED) {

	gvrender_begin_nodes(job);
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	    emit_node(job, n);
	gvrender_end_nodes(job);
	gvrender_begin_edges(job);
	for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	    for (e = agfstout(g, n); e; e = agnxtout(g, e))
		emit_edge(job, e);
	}
	gvrender_end_edges(job);
    } else if (flags & EMIT_EDGE_SORTED) {

	gvrender_begin_edges(job);
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	    for (e = agfstout(g, n); e; e = agnxtout(g, e))
		emit_edge(job, e);
	gvrender_end_edges(job);
	gvrender_begin_nodes(job);
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	    emit_node(job, n);
	gvrender_end_nodes(job);
    } else if (flags & EMIT_PREORDER) {
	gvrender_begin_nodes(job);
	for (n = agfstnode(g); n; n = agnxtnode(g, n))
	    if (write_node_test(g, n))
		emit_node(job, n);
	gvrender_end_nodes(job);
	gvrender_begin_edges(job);

	for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	    for (e = agfstout(g, n); e; e = agnxtout(g, e)) {
		if (write_edge_test(g, e))
		    emit_edge(job, e);
	    }
	}
	gvrender_end_edges(job);
    } else {

	for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	    emit_node(job, n);
	    for (e = agfstout(g, n); e; e = agnxtout(g, e)) {
		emit_node(job, aghead(e));
		emit_edge(job, e);
	    }
	}
    }

    if (flags & EMIT_CLUSTERS_LAST)
	emit_clusters(job, g, flags);
}
