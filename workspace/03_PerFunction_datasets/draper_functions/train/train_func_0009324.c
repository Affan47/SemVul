vertex_foreach_edge (Vertex * vertex, VertexEdgeFunc func, void * user_data)
{
    if (vertex == NULL) return;

    EdgeClosure closure = { vertex, func, user_data };
    dlist_foreach (vertex->edges, _edge_func, &closure);
}
