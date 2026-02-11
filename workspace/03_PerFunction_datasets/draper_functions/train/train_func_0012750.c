symb_node_set_from_map(int node)
{
    G_debug(2, "line_symb_refresh()");

    if (node > aNodeSymb) {
	aNodeSymb = node + 1000;
	NodeSymb = (int *)G_realloc(NodeSymb, (aNodeSymb + 1) * sizeof(int));
    }
    NodeSymb[node] = symb_node_from_map(node);
}
