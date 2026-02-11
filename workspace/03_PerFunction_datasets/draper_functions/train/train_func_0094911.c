make_noise_scars(const LNoSynthArgs *args,
                 const GwyDimensionArgs *dimsargs,
                 GwyDataField *dfield)
{
    const LNoSynthArgsScars *pargs = args->noise_args;
    const LNoSynthGenerator *generator;
    PointNoiseFunc point_noise;
    gdouble *data, *row;
    GRand *rngpos, *rnglen;
    gint xres, yres, i, j, length, from, to, L;
    guint is, n, nscars, m, t;
    gdouble noise_corr, stickout_corr, q, h;

    rngpos = g_rand_new();
    rnglen = g_rand_new();

    q = args->sigma * pow10(dimsargs->zpow10);
    xres = gwy_data_field_get_xres(dfield);
    yres = gwy_data_field_get_yres(dfield);
    n = xres*yres;
    L = pargs->length;

    noise_corr = exp(pargs->length_noise*pargs->length_noise);
    stickout_corr = (L + xres)/L;
    nscars = GWY_ROUND(pargs->coverage*n*stickout_corr/(L*noise_corr));
    nscars = MAX(nscars, 1);

    i = yres*(xres + L);
    m = G_MAXUINT32/i*i;

    generator = get_point_noise_generator(args->distribution);
    point_noise = generator->point_noise[args->direction];

    generator->base_generator(NULL, 0.0);
    rand_gen_gaussian(NULL, 0.0);
    g_rand_set_seed(rngpos, args->seed);
    g_rand_set_seed(rnglen, args->seed+1);

    data = gwy_data_field_get_data(dfield);
    for (is = 0; is < nscars; is++) {
        do {
            t = g_rand_int(rngpos);
        } while (t >= m);
        i = t % yres;
        j = t/yres % (xres + L) + L/2-L;
        h = point_noise(rngpos, q);
        if (pargs->length_noise)
            length = GWY_ROUND(L*exp(rand_gen_gaussian(rnglen,
                                                       pargs->length_noise)));
        else
            length = L;
        row = data + i*xres;
        from = MAX(j - length/2, 0);
        to = MIN(j+length - length/2, xres-1);
        for (j = from; j <= to; j++)
            row[j] += h;
    }

    g_rand_free(rngpos);
    g_rand_free(rnglen);
}
