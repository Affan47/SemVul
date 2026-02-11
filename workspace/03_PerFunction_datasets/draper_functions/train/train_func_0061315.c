flush_search_node(struct search_node *n, struct search *sr)
{
    int i = n - sr->nodes, j;
    for(j = i; j < sr->numnodes - 1; j++)
        sr->nodes[j] = sr->nodes[j + 1];
    sr->numnodes--;
}
