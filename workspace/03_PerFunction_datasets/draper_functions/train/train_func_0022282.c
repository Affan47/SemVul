CurTreeAddRank( CUR_TREE *cur_tree, AT_NUMB rank )
{
    if ( cur_tree ) {
        if ( cur_tree->cur_len + 2 > cur_tree->max_len ) {
            if ( CurTreeReAlloc( cur_tree ) ) {
                return -1;
            }
        }
        cur_tree->tree[cur_tree->cur_len++] = rank;
        cur_tree->tree[cur_tree->cur_len++] = 1;
        return 0;
    }
    return -1;
}
