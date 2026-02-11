add_tree_edge(edge_t * e)
{
    node_t *n;
    if (TREE_EDGE(e))
	abort();
    ED_tree_index(e) = Tree_edge.size;
    Tree_edge.list[Tree_edge.size++] = e;
    if (ND_mark(agtail(e)) == FALSE)
	Tree_node.list[Tree_node.size++] = agtail(e);
    if (ND_mark(aghead(e)) == FALSE)
	Tree_node.list[Tree_node.size++] = aghead(e);
    n = agtail(e);
    ND_mark(n) = TRUE;
    ND_tree_out(n).list[ND_tree_out(n).size++] = e;
    ND_tree_out(n).list[ND_tree_out(n).size] = NULL;
    n = aghead(e);
    ND_mark(n) = TRUE;
    ND_tree_in(n).list[ND_tree_in(n).size++] = e;
    ND_tree_in(n).list[ND_tree_in(n).size] = NULL;
}
