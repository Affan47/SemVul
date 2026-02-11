insert_edge_node(EdgeNode *n, EdgeNode *next)
{
    EdgeNode *prev;

    while(n) {
        prev = n;
        if(next->e->weight > n->e->weight)
            n = n->right;
        else
            n = n->left;
    }
    if(next->e->weight > prev->e->weight)
        prev->right = next;
    else
        prev->left = next;
}
