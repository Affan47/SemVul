make_lrvn(graph_t * g)
{
    node_t *ln, *rn;

    if (GD_ln(g))
	return;
    ln = virtual_node(agroot(g));
    ND_node_type(ln) = SLACKNODE;
    rn = virtual_node(agroot(g));
    ND_node_type(rn) = SLACKNODE;

    if (GD_label(g) && (g != agroot(g)) && !GD_flip(agroot(g))) {
	int w = MAX(GD_border(g)[BOTTOM_IX].x, GD_border(g)[TOP_IX].x);
	make_aux_edge(ln, rn, w, 0);
    }

    GD_ln(g) = ln;
    GD_rn(g) = rn;
}
