merge_ranks(graph_t * subg)
{
    int i, d, r, pos, ipos;
    node_t *v;
    graph_t *root;

    root = agroot(subg);
    if (GD_minrank(subg) > 0)
	GD_rank(root)[GD_minrank(subg) - 1].valid = FALSE;
    for (r = GD_minrank(subg); r <= GD_maxrank(subg); r++) {
	d = GD_rank(subg)[r].n;
	ipos = pos = ND_order(GD_rankleader(subg)[r]);
	make_slots(root, r, pos, d);
	for (i = 0; i < GD_rank(subg)[r].n; i++) {
	    v = GD_rank(root)[r].v[pos] = GD_rank(subg)[r].v[i];
	    ND_order(v) = pos++;

	    if (ND_node_type(v) == VIRTUAL)
		v->root = root;
	    delete_fast_node(subg, v);
	    fast_node(agroot(subg), v);
	    GD_n_nodes(agroot(subg))++;
	}
	GD_rank(subg)[r].v = GD_rank(root)[r].v + ipos;
	GD_rank(root)[r].valid = FALSE;
    }
    if (r < GD_maxrank(root))
	GD_rank(root)[r].valid = FALSE;
    GD_expanded(subg) = TRUE;
}
