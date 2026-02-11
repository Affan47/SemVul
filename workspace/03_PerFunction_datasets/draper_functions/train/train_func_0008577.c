anfatec_try_to_find_data(const gchar *dirname_glib,
                         const gchar *basename_sys)
{
    static const gchar *encodings[] = {
        "UTF-16", "CP1252", "CP1251", "CP1250", "CP1253", "CP1254", "CP1255",
        "CP1256", "CP1257", "CP1258",
    };
    guint i;
    gssize len = strlen(basename_sys);
    gchar *fullname_asis, G_GNUC_UNUSED *dirname_locale;
    FILE *fh;


    fullname_asis = g_build_filename(dirname_glib, basename_sys, NULL);
    gwy_debug("Trying as-is: <%s>", fullname_asis);
    fh = g_fopen(fullname_asis, "rb");
    if (!fh)
        fh = fopen(fullname_asis, "rb");
    g_free(fullname_asis);
    if (fh)
        return fh;

#ifdef G_OS_WIN32

    dirname_locale = g_win32_locale_filename_from_utf8(dirname_glib);
    if (dirname_locale) {
        gchar *fullname_locale = g_build_filename(dirname_locale, basename_sys,
                                                  NULL);

        g_free(dirname_locale);
        gwy_debug("Trying locale: <%s>", fullname_locale);
        fh = fopen(fullname_locale, "rb");
        g_free(fullname_locale);
        if (fh)
            return fh;
    }
#endif

    for (i = 0; i < G_N_ELEMENTS(encodings); i++) {
        gchar *filename_utf8 = g_convert(basename_sys, len,
                                         "UTF-8", encodings[i],
                                         NULL, NULL, NULL);
        if (filename_utf8) {
            gchar *filename_glib = g_filename_from_utf8(filename_utf8, -1,
                                                        NULL, NULL, NULL);

            g_free(filename_utf8);
            if (filename_glib) {
                gchar *fullname_glib = g_build_filename(dirname_glib,
                                                        filename_glib,
                                                        NULL);

                g_free(filename_glib);
                gwy_debug("Trying encoding %s: <%s>", encodings[i], fullname_glib);
                fh = g_fopen(fullname_glib, "rb");
                g_free(fullname_glib);

                if (fh)
                    return fh;
            }
        }
    }

    return NULL;
}
