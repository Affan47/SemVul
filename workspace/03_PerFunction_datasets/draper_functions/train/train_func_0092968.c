pointerize(struct veb *veb)
{
    int i;

    for (i=1; i < (1 << veb->height); i++)
    {
        struct tree_node *node = node_at(veb, i);

        if (!node_empty(node))
        {
            if (node_valid(veb, bfs_left(i)))
                node->left = node_at(veb, bfs_left(i));

            if (node_valid(veb, bfs_right(i)))
                node->right = node_at(veb, bfs_right(i));
        }
    }
}
