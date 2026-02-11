bee_subtree_successor(struct bee_subtree *node)
{
    node = node->right;

    if (!node)
        return NULL;

    while (node->left)
        node = node->left;

    return node;
}
