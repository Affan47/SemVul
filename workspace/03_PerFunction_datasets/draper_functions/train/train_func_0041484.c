dfs_enter_inedge(node_t * v)
{
    int i, slack;
    edge_t *e;

    for (i = 0; (e = ND_in(v).list[i]); i++) {
	if (TREE_EDGE(e) == FALSE) {
	    if (!SEQ(Low, ND_lim(agtail(e)), Lim)) {
		slack = SLACK(e);
		if ((slack < Slack) || (Enter == NULL)) {
		    Enter = e;
		    Slack = slack;
		}
	    }
	} else if (ND_lim(agtail(e)) < ND_lim(v))
	    dfs_enter_inedge(agtail(e));
    }
    for (i = 0; (e = ND_tree_out(v).list[i]) && (Slack > 0); i++)
	if (ND_lim(aghead(e)) < ND_lim(v))
	    dfs_enter_inedge(aghead(e));
}
