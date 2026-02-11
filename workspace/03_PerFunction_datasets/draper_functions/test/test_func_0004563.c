clear_branch(struct strie_pair *node)
{
    struct strie_pair *cur_node = node;
    struct strie_pair *next_node = NULL;

    if (!node)
        return 0;

    while (cur_node)
    {
        while (cur_node->firstchild)
            cur_node = cur_node->firstchild;

        if (!(next_node = cur_node->brother))
        {
            next_node = cur_node->parent;

            if (next_node)
            {


                next_node->firstchild = NULL;
            }
        }

        if (cur_node->available_first_children)
            free(cur_node->available_first_children);
        free(cur_node);

        cur_node = next_node;
    }

    return 0;
}
