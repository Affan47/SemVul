gwy_interpolation_resample_block_1d(gint length,
                                    gdouble *data,
                                    gint newlength,
                                    gdouble *newdata,
                                    GwyInterpolationType interpolation,
                                    gboolean preserve)
{
    gdouble *w, *coeffs = NULL;
    gdouble q, x0, x, v;
    gint i, ii, oldi, newi;
    gint suplen, sf, st;

    if (interpolation == GWY_INTERPOLATION_NONE)
        return;

    suplen = gwy_interpolation_get_support_size(interpolation);
    g_return_if_fail(suplen > 0);
    w = g_newa(gdouble, suplen);
    sf = -((suplen - 1)/2);
    st = suplen/2;

    if (!gwy_interpolation_has_interpolating_basis(interpolation)) {
        if (preserve)
            data = coeffs = g_memdup(data, length*sizeof(gdouble));
        gwy_interpolation_resolve_coeffs_1d(length, data, interpolation);
    }

    q = (gdouble)length/newlength;
    x0 = (q - 1.0)/2.0;
    for (newi = 0; newi < newlength; newi++) {
        x = q*newi + x0;
        oldi = (gint)floor(x);
        x -= oldi;
        gwy_interpolation_get_weights(x, interpolation, w);
        v = 0.0;
        for (i = sf; i <= st; i++) {
            ii = (oldi + i + 2*st*length) % (2*length);
            if (G_UNLIKELY(ii >= length))
                ii = 2*length-1 - ii;
            v += data[ii]*w[i - sf];
        }
        newdata[newi] = v;
    }

    g_free(coeffs);
}
