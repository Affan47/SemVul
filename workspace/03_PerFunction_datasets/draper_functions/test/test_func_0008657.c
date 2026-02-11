node_deq_each(Node **q, void (*iter)(Node *))
{
    if(!q)
        return;

    if(!iter)
        iter = free_node;

    Node *n;
    while((n = node_deq(q)))
        iter(n);
}
