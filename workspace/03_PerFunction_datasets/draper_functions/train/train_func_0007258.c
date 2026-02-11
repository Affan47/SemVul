collapse_rankset(graph_t * g, graph_t * subg, int kind)
{
    node_t *u, *v;

    u = v = agfstnode(subg);
    if (u) {
	ND_ranktype(u) = kind;
	while ((v = agnxtnode(subg, v))) {
	    UF_union(u, v);
	    ND_ranktype(v) = ND_ranktype(u);
	}
	switch (kind) {
	case MINRANK:
	case SOURCERANK:
	    if (GD_minset(g) == NULL)
		GD_minset(g) = u;
	    else
		GD_minset(g) = UF_union(GD_minset(g), u);
	    break;
	case MAXRANK:
	case SINKRANK:
	    if (GD_maxset(g) == NULL)
		GD_maxset(g) = u;
	    else
		GD_maxset(g) = UF_union(GD_maxset(g), u);
	    break;
	}
	switch (kind) {
	case SOURCERANK:
	    ND_ranktype(GD_minset(g)) = kind;
	    break;
	case SINKRANK:
	    ND_ranktype(GD_maxset(g)) = kind;
	    break;
	}
    }
}
