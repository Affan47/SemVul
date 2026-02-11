compare_plist(plist_t node_l, plist_t node_r)
{
    plist_t cur_l = NULL;
    plist_t cur_r = NULL;
    int res = 1;

    cur_l = plist_get_first_child(node_l);
    cur_r = plist_get_first_child(node_r);

    if ( (!cur_l && cur_r) || (cur_l && !cur_r))
        return 0;

    if ( !cur_l && !cur_r )
        return plist_compare_node_value( node_l, node_r );

    while (cur_l && cur_r && res)
    {

        if (!(res = compare_plist(cur_l, cur_r)))
            return res;

        cur_l = plist_get_next_sibling(cur_l);
        cur_r = plist_get_next_sibling(cur_r);
        if ( (!cur_l && cur_r) || (cur_l && !cur_r))
            return 0;
    }

    return res;
}
