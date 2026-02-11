recalc_divide_sub(const lame_internal_flags * const gfc,
                  const gr_info * cod_info2,
                  gr_info * const gi,
                  const int *const ix,
                  const int r01_bits[], const int r01_div[], const int r0_tbl[], const int r1_tbl[])
{
    int     bits, r2, a2, bigv, r2t;

    bigv = cod_info2->big_values;

    for (r2 = 2; r2 < SBMAX_l + 1; r2++) {
        a2 = gfc->scalefac_band.l[r2];
        if (a2 >= bigv)
            break;

        bits = r01_bits[r2 - 2] + cod_info2->count1bits;
        if (gi->part2_3_length <= bits)
            break;

        r2t = gfc->choose_table(ix + a2, ix + bigv, &bits);
        if (gi->part2_3_length <= bits)
            continue;

        memcpy(gi, cod_info2, sizeof(gr_info));
        gi->part2_3_length = bits;
        gi->region0_count = r01_div[r2 - 2];
        gi->region1_count = r2 - 2 - r01_div[r2 - 2];
        gi->table_select[0] = r0_tbl[r2 - 2];
        gi->table_select[1] = r1_tbl[r2 - 2];
        gi->table_select[2] = r2t;
    }
}
