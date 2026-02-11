graph_node_assoc_append(graph_node *node, graph_edge *edge)
{
    if (node->assoc_edge_count == 0) {
        node->assoc_edge = (graph_edge**)malloc(sizeof(graph_edge*));
    } else {
        node->assoc_edge = (graph_edge**)realloc(node->assoc_edge, (node->assoc_edge_count + 1) * sizeof(graph_edge*));
    }

    if (node->assoc_edge_count > 1
        && node->assoc_edge[node->assoc_edge_count - 1] == edge) {
        return;
    }

    node->assoc_edge[node->assoc_edge_count] = edge;
    node->assoc_edge_count++;
}
