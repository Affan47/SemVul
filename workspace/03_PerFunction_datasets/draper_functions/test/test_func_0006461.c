vbrpsy_skip_masking_s(lame_internal_flags * gfc, int chn, int sblock)
{
    if (sblock == 0) {
        FLOAT  *nbs2 = &gfc->sv_psy.nb_s2[chn][0];
        FLOAT  *nbs1 = &gfc->sv_psy.nb_s1[chn][0];
        int const n = gfc->cd_psy->s.npart;
        int     b;
        if (gfc->cfg.vbr == vbr_mt) {
            for (b = 0; b < n; b++) {
                nbs2[b] = nbs1[b];
            }
        }
        else {
            for (b = 0; b < n; b++) {
                nbs2[b] = nbs1[b];
                nbs1[b] = 0;
            }
        }
    }
}
