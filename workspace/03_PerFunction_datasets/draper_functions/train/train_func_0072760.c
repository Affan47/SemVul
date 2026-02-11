LR_balance(void)
{
    int i, delta;
    node_t *n;
    edge_t *e, *f;

    for (i = 0; i < Tree_edge.size; i++) {
	e = Tree_edge.list[i];
	if (ED_cutvalue(e) == 0) {
	    f = enter_edge(e);
	    if (f == NULL)
		continue;
	    delta = SLACK(f);
	    if (delta <= 1)
		continue;
	    if (ND_lim(agtail(e)) < ND_lim(aghead(e)))
		rerank(agtail(e), delta / 2);
	    else
		rerank(aghead(e), -delta / 2);
	}
    }
    for (n = agfstnode(G); n; n = agnxtnode(G, n)) {
	free_list(ND_tree_in(n));
	free_list(ND_tree_out(n));
	ND_mark(n) = FALSE;
    }
}
