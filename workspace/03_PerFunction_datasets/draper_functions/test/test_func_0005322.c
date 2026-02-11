bfs_first(struct veb *veb, int subtree_root)
{
    int bfs = subtree_root;

    fill_pos(veb->level_info, subtree_root, veb->iter_pos);

    if (!node_valid_pos(veb, bfs))
        return -1;

    while (node_valid_pos(veb, bfs))
        bfs = bfs_left(bfs);

    return bfs_parent(bfs);
}
