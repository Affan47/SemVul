convert_partition2scalefac_l(lame_internal_flags * gfc, FLOAT const *eb, FLOAT const *thr, int chn)
{
    FLOAT   enn, thmm;
    int     sb, b;
    enn = thmm = 0.0;
    for (sb = b = 0; sb < SBMAX_l; ++b, ++sb) {
        int const bo_l_sb = gfc->bo_l[sb];
        int const npart_l = gfc->npart_l;
        int const b_lim = bo_l_sb < npart_l ? bo_l_sb : npart_l;
        while (b < b_lim) {
            assert(eb[b] >= 0);
            assert(thr[b] >= 0);
            enn += eb[b];
            thmm += thr[b];
            b++;
        }
        gfc->en[chn].l[sb] = enn;
        gfc->thm[chn].l[sb] = thmm;

        if (b >= npart_l) {
            ++sb;
            break;
        }
        assert(eb[b] >= 0);
        assert(thr[b] >= 0);
        {

            FLOAT const w_curr = gfc->PSY->bo_l_weight[sb];
            FLOAT const w_next = 1.0 - w_curr;
            enn = w_curr * eb[b];
            thmm = w_curr * thr[b];
            gfc->en[chn].l[sb] += enn;
            gfc->thm[chn].l[sb] += thmm;
            enn = w_next * eb[b];
            thmm = w_next * thr[b];
        }
    }

    for (; sb < SBMAX_l; ++sb) {
        gfc->en[chn].l[sb] = 0;
        gfc->thm[chn].l[sb] = 0;
    }
}
