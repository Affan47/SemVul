new_graph(unsigned opts)
{
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if(!g)
        return 0;

    g->max = 4;

    if(!(g->verts = (Vert **) malloc(sizeof(Vert *) * g->max))) {
        free(g);
        return 0;
    }

    *g->verts = 0;
    g->edge_nodes = 0;
    g->len = 1;
    g->opts = opts;

    return g;
}
