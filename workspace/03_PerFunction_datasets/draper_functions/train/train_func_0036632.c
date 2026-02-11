huffman_init(lame_internal_flags * const gfc)
{
    int     i;

    gfc->choose_table = choose_table_nonMMX;

#ifdef MMX_choose_table
    if (gfc->CPU_features.MMX) {
        gfc->choose_table = choose_table_MMX;
    }
#endif

    for (i = 2; i <= 576; i += 2) {
        int     scfb_anz = 0, bv_index;
        while (gfc->scalefac_band.l[++scfb_anz] < i);

        bv_index = subdv_table[scfb_anz].region0_count;
        while (gfc->scalefac_band.l[bv_index + 1] > i)
            bv_index--;

        if (bv_index < 0) {


            bv_index = subdv_table[scfb_anz].region0_count;
        }

        gfc->sv_qnt.bv_scf[i - 2] = bv_index;

        bv_index = subdv_table[scfb_anz].region1_count;
        while (gfc->scalefac_band.l[bv_index + gfc->sv_qnt.bv_scf[i - 2] + 2] > i)
            bv_index--;

        if (bv_index < 0) {
            bv_index = subdv_table[scfb_anz].region1_count;
        }

        gfc->sv_qnt.bv_scf[i - 1] = bv_index;
    }
}
