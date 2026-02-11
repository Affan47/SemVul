reset_region_mids(NhRegion *reg)
{
    int i = 0, n = reg->n_monst;
    unsigned *mid_list = reg->monsters;

    while (i < n)
            if (!lookup_id_mapping(mid_list[i], &mid_list[i]))
            {

                mid_list[i] = mid_list[--n];
            }
            else
            {

                ++i;
            }
    reg->n_monst = n;
    return;
}
