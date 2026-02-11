mds_model(graph_t * g, int nG)
{
    long i, j;
    node_t *v;
    edge_t *e;

    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	for (e = agfstout(g, v); e; e = agnxtout(g, e)) {
	    i = AGSEQ(agtail(e));
	    j = AGSEQ(aghead(e));
	    if (i == j)
		continue;
	    GD_dist(g)[i][j] = GD_dist(g)[j][i] = ED_dist(e);
	}
    }
}
