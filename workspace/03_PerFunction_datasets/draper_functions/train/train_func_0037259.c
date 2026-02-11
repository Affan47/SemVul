removeFill (Agraph_t * g)
{
    Agnode_t* n;
    Agnode_t* nxt;
    Agraph_t* sg = agsubg (g, "_new_rank", 0);

    if (!sg) return;
    for (n = agfstnode(sg); n; n = nxt) {
	nxt = agnxtnode(sg, n);
	delete_fast_node (g, n);
	remove_from_rank (g, n);
	dot_cleanup_node (n);
	agdelnode(g, n);
    }
    agdelsubg (g, sg);

}
