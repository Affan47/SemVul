omicronflat_readsps(GwyContainer *container, GwyContainer *metainfo,
                    const guchar **fp, const gsize fp_end, GError **error)
{
    guint32 i, j, n, navail, nexpect;
    gchar *t;
    GQuark quark;
    gboolean mirrored;
    gdouble length, width;
    gdouble fac = 1.;
    gdouble offset = 0;
    gdouble spec_offset = 0;

    GwySpectra *spectra = NULL;
    const guchar* sunit;
    GwySIUnit *unitx = NULL;
    GwySIUnit *unity = NULL;
    GwyDataLine *dline;
    gdouble *data;

    gwy_debug("File is spectroscopy curves (SPS) ");

    nexpect = gwy_container_get_int32_by_name(metainfo, "brickletSize");
    navail = gwy_container_get_int32_by_name(metainfo, "dataItemSize");

    if (navail > nexpect) {
        err_FILE_TYPE(error, "Omicron Flat");
        return;
    }


    if (fp_end < (gsize)*fp + navail*4) {
        err_TOO_SHORT(error);
        return;
    }

    mirrored = gwy_container_get_boolean_by_name(metainfo,
                                                "/axis/0/mirrored");
    length = gwy_container_get_int32_by_name(metainfo,
                                                "/axis/0/clockCount")
             / (mirrored+1);
    width = gwy_container_get_double_by_name(metainfo,
                                                "/axis/0/incrementPhysical")
            * length;
    spec_offset = gwy_container_get_double_by_name(metainfo,
                                            "/axis/0/startValuePhysical");


    if (length * (mirrored+1) != nexpect) {
        err_FILE_TYPE(error, "Omicron Flat");
        return;
    }

    sunit = gwy_container_get_string_by_name(metainfo, "/axis/0/units");
    unitx = gwy_si_unit_new((gchar*)sunit);

    sunit = gwy_container_get_string_by_name(metainfo, "/channel/units");
    unity = gwy_si_unit_new((gchar*)sunit);

    omicronflat_getscalingfactor(metainfo, &fac, &offset);
    spectra = gwy_spectra_new();
    n = 0;


    for (i = 0; i < (mirrored+1); ++i) {

        dline = gwy_data_line_new(length, width, TRUE);
        gwy_data_line_set_si_unit_x(dline, unitx);
        gwy_data_line_set_si_unit_y(dline, unity);
        gwy_data_line_set_offset(dline, spec_offset);
        data = gwy_data_line_get_data(dline);

        for (j = 0; j < length && n < navail; ++j) {
            data[j] = fac * (gwy_get_gint32_le(fp)-offset);
            ++n;
        }

        gwy_spectra_add_spectrum(spectra, dline, 0, 0);


        g_object_unref(dline);
    }


    if (n != navail) {
        err_FILE_TYPE(error, "Omicron Flat");
        return;
    }

    gwy_debug("SPS data successfully read");


    t = g_strconcat("Spectroscopy", NULL);
    gwy_spectra_set_title(spectra, t);
    quark = gwy_app_get_spectra_key_for_id(0);
    gwy_container_set_object(container, quark, spectra);

    g_free(t);
    g_object_unref(unitx);
    g_object_unref(unity);
    g_object_unref(spectra);

    return;
}
