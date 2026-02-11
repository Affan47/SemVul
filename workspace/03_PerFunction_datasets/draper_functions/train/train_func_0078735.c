fnt_autoconvolute(mpd_uint_t *c1, mpd_size_t n, int modnum)
{
    int (*fnt)(mpd_uint_t *, mpd_size_t, int);
    int (*inv_fnt)(mpd_uint_t *, mpd_size_t, int);
#ifdef PPRO
    double dmod;
    uint32_t dinvmod[3];
#endif
    mpd_uint_t n_inv, umod;
    mpd_size_t i;


    SETMODULUS(modnum);
    n_inv = POWMOD(n, (umod-2));

    if (ispower2(n)) {
        if (n > SIX_STEP_THRESHOLD) {
            fnt = six_step_fnt;
            inv_fnt = inv_six_step_fnt;
        }
        else {
            fnt = std_fnt;
            inv_fnt = std_inv_fnt;
        }
    }
    else {
        fnt = four_step_fnt;
        inv_fnt = inv_four_step_fnt;
    }

    if (!fnt(c1, n, modnum)) {
        return 0;
    }
    for (i = 0; i < n-1; i += 2) {
        mpd_uint_t x0 = c1[i];
        mpd_uint_t x1 = c1[i+1];
        MULMOD2(&x0, x0, &x1, x1);
        c1[i] = x0;
        c1[i+1] = x1;
    }

    if (!inv_fnt(c1, n, modnum)) {
        return 0;
    }
    for (i = 0; i < n-3; i += 4) {
        mpd_uint_t x0 = c1[i];
        mpd_uint_t x1 = c1[i+1];
        mpd_uint_t x2 = c1[i+2];
        mpd_uint_t x3 = c1[i+3];
        MULMOD2C(&x0, &x1, n_inv);
        MULMOD2C(&x2, &x3, n_inv);
        c1[i] = x0;
        c1[i+1] = x1;
        c1[i+2] = x2;
        c1[i+3] = x3;
    }

    return 1;
}
