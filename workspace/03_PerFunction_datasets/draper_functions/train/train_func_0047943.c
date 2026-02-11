pop_edge_node(EdgeNode **stack)
{
    if(!stack || !*stack)
        return 0;

    EdgeNode *pop = (*stack)->left,
            *next = (*stack)->right;

    free(*stack);
    *stack = next;

    return pop;
}
