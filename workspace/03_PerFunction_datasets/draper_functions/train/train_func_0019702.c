get_start_end_time_of_blocks_for_one_pe(Block *bhead, int mt_num,
                                        real **start, real **end)
{
    Block *bpt;
    real st = 0.0;
    real *sp, *ep;

    sp = zcalloc(mt_num + 1, sizeof(real));
    ep = zcalloc(mt_num + 1, sizeof(real));
    for (bpt = bhead; bpt != NULL; bpt = bpt->next) {
        int no = bpt->no;
        sp[no] = st;
        ep[no] = st + bpt->cost + 1;
        st = ep[no] + 1;
    }
    *start = sp;
    *end = ep;
}
