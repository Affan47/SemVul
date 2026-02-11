lame_init_params_ppflt(lame_internal_flags * gfc)
{
    SessionConfig_t *const cfg = &gfc->cfg;


    int     band, maxband, minband;
    FLOAT   freq;
    int     lowpass_band = 32;
    int     highpass_band = -1;

    if (cfg->lowpass1 > 0) {
        minband = 999;
        for (band = 0; band <= 31; band++) {
            freq = band / 31.0;

            if (freq >= cfg->lowpass2) {
                lowpass_band = Min(lowpass_band, band);
            }
            if (cfg->lowpass1 < freq && freq < cfg->lowpass2) {
                minband = Min(minband, band);
            }
        }


        if (minband == 999) {
            cfg->lowpass1 = (lowpass_band - .75) / 31.0;
        }
        else {
            cfg->lowpass1 = (minband - .75) / 31.0;
        }
        cfg->lowpass2 = lowpass_band / 31.0;
    }


    if (cfg->highpass2 > 0) {
        if (cfg->highpass2 < .9 * (.75 / 31.0)) {
            cfg->highpass1 = 0;
            cfg->highpass2 = 0;
            MSGF(gfc, "Warning: highpass filter disabled.  " "highpass frequency too small\n");
        }
    }

    if (cfg->highpass2 > 0) {
        maxband = -1;
        for (band = 0; band <= 31; band++) {
            freq = band / 31.0;

            if (freq <= cfg->highpass1) {
                highpass_band = Max(highpass_band, band);
            }
            if (cfg->highpass1 < freq && freq < cfg->highpass2) {
                maxband = Max(maxband, band);
            }
        }


        cfg->highpass1 = highpass_band / 31.0;
        if (maxband == -1) {
            cfg->highpass2 = (highpass_band + .75) / 31.0;
        }
        else {
            cfg->highpass2 = (maxband + .75) / 31.0;
        }
    }

    for (band = 0; band < 32; band++) {
        FLOAT fc1, fc2;
        freq = band / 31.0f;
        if (cfg->highpass2 > cfg->highpass1) {
            fc1 = filter_coef((cfg->highpass2 - freq) / (cfg->highpass2 - cfg->highpass1 + 1e-20));
        }
        else {
            fc1 = 1.0f;
        }
        if (cfg->lowpass2 > cfg->lowpass1) {
            fc2 = filter_coef((freq - cfg->lowpass1)  / (cfg->lowpass2 - cfg->lowpass1 + 1e-20));
        }
        else {
            fc2 = 1.0f;
        }
        gfc->sv_enc.amp_filter[band] = fc1 * fc2;
    }
}
