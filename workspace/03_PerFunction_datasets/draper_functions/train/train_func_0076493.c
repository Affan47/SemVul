veb_tree_insert(struct veb *veb, btrfs_key_t *search_key)
{
    int res;
    int d;
    int cmp;
    int bfs_num = 1;
    int pos[MAX_HEIGHT];
    struct level_info *l = veb->level_info;

    pos[0] = 0;
    for (d=0; d < veb->height; d++)
    {
#ifdef TEST_BFS
        struct tree_node *node = node_at(veb, bfs_num);
#else
        pos[d] = pos[l[d].subtree_depth] + l[d].top_size +
            (bfs_num & l[d].top_size) * (l[d].bottom_size);

        struct tree_node *node = &veb->elements[pos[d]];
#endif

        if (node_empty(node))
        {
            memcpy(&node->key, search_key, sizeof(*search_key));
            veb->count++;
            return 0;
        }

        cmp = compare_key(search_key, &node->key);

        if (cmp < 0)
            bfs_num = bfs_left(bfs_num);
        else if (cmp > 0)
            bfs_num = bfs_right(bfs_num);
        else
            return 0;
    }

    res = veb_tree_rebalance(veb, bfs_parent(bfs_num), search_key);


    if (res == -1)
        return veb_tree_insert(veb, search_key);

    return 0;
}
