init_UF_size(graph_t * g)
{
    node_t *n;

    for (n = agfstnode(g); n; n = agnxtnode(g, n))
	ND_UF_size(n) = 0;
}
