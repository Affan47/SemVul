fill_displacement_map(GwyDataField *dfield,
                      GRand *rng,
                      gdouble q)
{
    GrowingIter giter;
    guint xres, yres;
    gdouble *data;

    xres = gwy_data_field_get_xres(dfield);
    yres = gwy_data_field_get_yres(dfield);
    g_return_if_fail(xres == yres);
    data = gwy_data_field_get_data(dfield);
    growing_iter_init(&giter, xres);

    do {
        data[giter.k] = q*(g_rand_double(rng) - 0.5);
    } while (growing_iter_next(&giter));
}
