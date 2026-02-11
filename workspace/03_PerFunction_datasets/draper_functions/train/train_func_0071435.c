neato_init_graph (Agraph_t * g)
{
    int outdim;

    setEdgeType (g, ET_LINE);
    outdim = late_int(g, agfindgraphattr(g, "dimen"), 2, 2);
    GD_ndim(agroot(g)) = late_int(g, agfindgraphattr(g, "dim"), outdim, 2);
    Ndim = GD_ndim(g->root) = MIN(GD_ndim(g->root), MAXDIM);
    GD_odim(g->root) = MIN(outdim, Ndim);
    neato_init_node_edge(g);
}
