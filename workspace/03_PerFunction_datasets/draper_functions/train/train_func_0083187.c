nanonics_read_data_field(const NanonicsFile *nfile,
                         guint id,
                         gboolean retrace,
                         const guchar *buffer)
{
    const gint16 *d16 = (const gint16*)buffer;
    GwyDataField *dfield;
    GwySIUnit *siunit;
    gint xres, yres, i, j, power10;
    gdouble *d;
    gchar *s;

    xres = nfile->xres;
    yres = nfile->yres;
    dfield = gwy_data_field_new(xres, yres, nfile->xreal, nfile->yreal, FALSE);
    d = gwy_data_field_get_data(dfield);

    for (i = 0; i < yres; i++) {
        if (retrace) {
            for (j = 0; j < xres; j++) {
                gint16 v = d16[(i + 1)*2*xres - 1 - j];
                *(d++) = GINT16_FROM_BE(v);
            }
        }
        else {
            for (j = 0; j < xres; j++) {
                gint16 v = d16[i*2*xres + j];
                *(d++) = GINT16_FROM_BE(v);
            }
        }
    }

    siunit = gwy_data_field_get_si_unit_xy(dfield);
    gwy_si_unit_set_from_string(siunit, "m");

    if ((s = g_hash_table_lookup(nfile->pagemeta[id], "CHU"))) {


        if (gwy_strequal(s, "Pi")) {
            gwy_data_field_multiply(dfield, G_PI);
            s[0] = '\0';
        }
        if (g_str_has_suffix(s, "Volts"))
            s[strlen(s) - strlen("Volts") + 1] = '\0';
        else if (g_str_has_suffix(s, "Newton"))
            s[strlen(s) - strlen("Newton") + 1] = '\0';

        siunit = gwy_data_field_get_si_unit_z(dfield);
        gwy_si_unit_set_from_string_parse(siunit, s, &power10);

        if (power10)
            gwy_data_field_multiply(dfield, pow10(power10));
    }

    return dfield;
}
