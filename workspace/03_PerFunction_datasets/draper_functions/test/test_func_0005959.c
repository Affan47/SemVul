vbrpsy_compute_fft_l(lame_global_flags const *gfp, const sample_t * buffer[2], int chn, int gr_out,
                     FLOAT fftenergy[HBLKSIZE], FLOAT(*wsamp_l)[BLKSIZE])
{
    lame_internal_flags *const gfc = gfp->internal_flags;
    int     j;

    if (chn < 2) {
        fft_long(gfc, *wsamp_l, chn, buffer);
    }
    else if (chn == 2) {

        for (j = BLKSIZE - 1; j >= 0; --j) {
            FLOAT const l = wsamp_l[0][j];
            FLOAT const r = wsamp_l[1][j];
            wsamp_l[0][j] = (l + r) * (FLOAT) (SQRT2 * 0.5);
            wsamp_l[1][j] = (l - r) * (FLOAT) (SQRT2 * 0.5);
        }
    }


    fftenergy[0] = NON_LINEAR_SCALE_ENERGY(wsamp_l[0][0]);
    fftenergy[0] *= fftenergy[0];

    for (j = BLKSIZE / 2 - 1; j >= 0; --j) {
        FLOAT const re = (*wsamp_l)[BLKSIZE / 2 - j];
        FLOAT const im = (*wsamp_l)[BLKSIZE / 2 + j];
        fftenergy[BLKSIZE / 2 - j] = NON_LINEAR_SCALE_ENERGY((re * re + im * im) * 0.5f);
    }

    {
        FLOAT   totalenergy = 0.0;
        for (j = 11; j < HBLKSIZE; j++)
            totalenergy += fftenergy[j];

        gfc->tot_ener[chn] = totalenergy;
    }

    if (gfp->analysis) {
        for (j = 0; j < HBLKSIZE; j++) {
            gfc->pinfo->energy[gr_out][chn][j] = gfc->pinfo->energy_save[chn][j];
            gfc->pinfo->energy_save[chn][j] = fftenergy[j];
        }
        gfc->pinfo->pe[gr_out][chn] = gfc->pe[chn];
    }
}
