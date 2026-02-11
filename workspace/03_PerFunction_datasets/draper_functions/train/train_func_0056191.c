set_cmp_localize_tlg(Block *block_head, const int tlg_tag, int offset)
{
    int dmax = get_max_dlg_tag(block_head, tlg_tag);
    int i;
    int t, max;

    max = 0;
    for (i = 1; i<= dmax; i++) {
        t = set_cmp_localize_dlg(block_head, tlg_tag, i, offset);
        if (t > max) {
            max = t;
        }
    }

    return max;
}
