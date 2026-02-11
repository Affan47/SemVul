make_edge_pairs(graph_t * g)
{
    int i, m0, m1;
    node_t *n, *sn;
    edge_t *e;

    for (n = GD_nlist(g); n; n = ND_next(n)) {
	if (ND_save_out(n).list)
	    for (i = 0; (e = ND_save_out(n).list[i]); i++) {
		sn = virtual_node(g);
		ND_node_type(sn) = SLACKNODE;
		m0 = (ED_head_port(e).p.x - ED_tail_port(e).p.x);
		if (m0 > 0)
		    m1 = 0;
		else {
		    m1 = -m0;
		    m0 = 0;
		}
#ifdef NOTDEF

		if ((ND_save_out(n).size % 2 == 0)
		    && (i == ND_save_out(n).size / 2 - 1)) {
		    node_t *u = ND_save_out(n).list[i]->head;
		    node_t *v = ND_save_out(n).list[i + 1]->head;
		    double width = ND_rw(u) + ND_lw(v) + GD_nodesep(g);
		    m0 = width / 2 - 1;
		}
#endif
		make_aux_edge(sn, agtail(e), m0 + 1, ED_weight(e));
		make_aux_edge(sn, aghead(e), m1 + 1, ED_weight(e));
		ND_rank(sn) =
		    MIN(ND_rank(agtail(e)) - m0 - 1,
			ND_rank(aghead(e)) - m1 - 1);
	    }
    }
}
