dot_rev_graph_nodes (rev_list *rl, char *title)
{
    rev_ref	*h;
    rev_commit	*c, *p;
    int		tail;

    printf ("nodesep=0.1;\n");
    printf ("ranksep=0.1;\n");
    printf ("edge [dir=none];\n");
    printf ("node [shape=box,fontsize=6];\n");
    dot_refs (rl, rl->heads, title, "ellipse");
    dot_tags (rl, title, "diamond");
    for (h = rl->heads; h; h = h->next) {
	if (h->tail)
	    continue;
	for (c = h->commit; c; c = p) {
	    p = dump_get_rev_parent (c);
	    tail = c->tail;
	    if (!p)
		break;
	    printf ("\t");
	    dot_commit_graph (c, h);
	    printf (" -> ");
	    dot_commit_graph (p, tail ? h->parent : h);
	    if (!tail)
		printf (" [weight=10];");
	    printf ("\n");
	    if (tail)
		break;
	}
    }
}
