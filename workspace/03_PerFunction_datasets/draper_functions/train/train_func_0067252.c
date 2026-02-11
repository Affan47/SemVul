make_interclust_chain(graph_t * g, node_t * from, node_t * to, edge_t * orig)
{
    int newtype;
    node_t *u, *v;

    u = map_interclust_node(from);
    v = map_interclust_node(to);
    if ((u == from) && (v == to))
	newtype = VIRTUAL;
    else
	newtype = CLUSTER_EDGE;
    map_path(u, v, orig, ED_to_virt(orig), newtype);
}
