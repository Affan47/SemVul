hash_to_data_field(GHashTable *hash,
                   const guchar *buffer,
                   gsize size,
                   GError **error)
{
    GwyDataField *dfield;
    GwySIUnit *unitz, *unitxy;
    gchar *val;
    gint xres, yres, i, j;
    gdouble xreal, yreal, q;
    gdouble *data;
    const gint16 *d16;

    if (!require_keys(hash, error, "num_samp", "scan_sz", "z_scale", NULL))
        return NULL;

    val = g_hash_table_lookup(hash, "num_samp");
    xres = yres = atoi(val);
    if (err_DIMENSION(error, xres))
        return NULL;

    if (err_SIZE_MISMATCH(error, xres*yres*sizeof(gint16), size, FALSE))
        return NULL;

    val = g_hash_table_lookup(hash, "scan_sz");
    xreal = yreal = Nanometer*g_ascii_strtod(val, NULL);
    if (xreal <= 0) {
        err_INVALID(error, "scan_sz");
        return NULL;
    }

    val = g_hash_table_lookup(hash, "z_scale");
    q = Nanometer/16384.0*g_ascii_strtod(val, NULL);
    if (q <= 0.0) {
        err_INVALID(error, "scan_sz");
        return NULL;
    }
    dfield = gwy_data_field_new(xres, yres, xreal, yreal, FALSE);
    data = gwy_data_field_get_data(dfield);
    d16 = (const gint16*)buffer;

    for (i = 0; i < yres; i++) {
        for (j = 0; j < xres; j++)
            data[(yres-1 - i)*xres + j] = q*GINT16_FROM_LE(d16[i*xres + j]);
    }

    unitz = gwy_si_unit_new("m");
    gwy_data_field_set_si_unit_z(dfield, unitz);
    g_object_unref(unitz);

    unitxy = gwy_si_unit_new("m");
    gwy_data_field_set_si_unit_xy(dfield, unitxy);
    g_object_unref(unitxy);

    return dfield;
}
