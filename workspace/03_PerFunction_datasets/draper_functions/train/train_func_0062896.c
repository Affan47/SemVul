vbrpsy_compute_fft_l(lame_internal_flags * gfc, const sample_t * const buffer[2], int chn,
                     int gr_out, FLOAT fftenergy[HBLKSIZE], FLOAT(*wsamp_l)[BLKSIZE])
{
    SessionConfig_t const *const cfg = &gfc->cfg;
    PsyStateVar_t *psv = &gfc->sv_psy;
    plotting_data *plt = cfg->analysis ? gfc->pinfo : 0;
    int     j;

    if (chn < 2) {
        fft_long(gfc, *wsamp_l, chn, buffer);
    }
    else if (chn == 2) {
        FLOAT const sqrt2_half = SQRT2 * 0.5f;

        for (j = BLKSIZE - 1; j >= 0; --j) {
            FLOAT const l = wsamp_l[0][j];
            FLOAT const r = wsamp_l[1][j];
            wsamp_l[0][j] = (l + r) * sqrt2_half;
            wsamp_l[1][j] = (l - r) * sqrt2_half;
        }
    }


    fftenergy[0] = wsamp_l[0][0];
    fftenergy[0] *= fftenergy[0];

    for (j = BLKSIZE / 2 - 1; j >= 0; --j) {
        FLOAT const re = (*wsamp_l)[BLKSIZE / 2 - j];
        FLOAT const im = (*wsamp_l)[BLKSIZE / 2 + j];
        fftenergy[BLKSIZE / 2 - j] = (re * re + im * im) * 0.5f;
    }

    {
        FLOAT   totalenergy = 0.0f;
        for (j = 11; j < HBLKSIZE; j++)
            totalenergy += fftenergy[j];

        psv->tot_ener[chn] = totalenergy;
    }

    if (plt) {
        for (j = 0; j < HBLKSIZE; j++) {
            plt->energy[gr_out][chn][j] = plt->energy_save[chn][j];
            plt->energy_save[chn][j] = fftenergy[j];
        }
    }
}
