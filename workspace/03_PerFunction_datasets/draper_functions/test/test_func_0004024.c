send_all_trees(s, lcodes, dcodes, blcodes)
    deflate_state *s;
    int lcodes, dcodes, blcodes;
{
    int rank;

    Assert (lcodes >= 257 && dcodes >= 1 && blcodes >= 4, "not enough codes");
    Assert (lcodes <= L_CODES && dcodes <= D_CODES && blcodes <= BL_CODES,
            "too many codes");
    Tracev((stderr, "\nbl counts: "));
    send_bits(s, lcodes-257, 5);
    send_bits(s, dcodes-1,   5);
    send_bits(s, blcodes-4,  4);
    for (rank = 0; rank < blcodes; rank++) {
        Tracev((stderr, "\nbl code %2d ", bl_order[rank]));
        send_bits(s, s->bl_tree[bl_order[rank]].Len, 3);
    }
    Tracev((stderr, "\nbl tree: sent %ld", s->bits_sent));

    send_tree(s, (ct_data *)s->dyn_ltree, lcodes-1);
    Tracev((stderr, "\nlit tree: sent %ld", s->bits_sent));

    send_tree(s, (ct_data *)s->dyn_dtree, dcodes-1);
    Tracev((stderr, "\ndist tree: sent %ld", s->bits_sent));
}
