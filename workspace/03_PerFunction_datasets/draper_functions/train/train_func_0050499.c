furthestnode(graph_t * g, node_t * v, int dir)
{
    node_t *u, *rv;

    rv = u = v;
    while ((u = neighbor(u, dir))) {
	if (is_a_normal_node_of(g, u))
	    rv = u;
	else if (is_a_vnode_of_an_edge_of(g, u))
	    rv = u;
    }
    return rv;
}
