packSubgraphs(int ng, Agraph_t ** gs, Agraph_t * root, pack_info * info)
{
    int ret;

    ret = packGraphs(ng, gs, root, info);
    if (ret == 0) {
	int i, j;
	boxf bb;
	graph_t* g;

	compute_bb(root);
	bb = GD_bb(root);
	for (i = 0; i < ng; i++) {
	    g = gs[i];
	    for (j = 1; j <= GD_n_cluster(g); j++) {
		EXPANDBB(bb,GD_bb(GD_clust(g)[j]));
	    }
	}
	GD_bb(root) = bb;
    }
    return ret;
}
