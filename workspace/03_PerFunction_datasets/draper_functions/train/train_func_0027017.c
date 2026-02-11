gwy_app_settings_save(const gchar *filename,
                      GError **error)
{
    GwyContainer *settings;
    GPtrArray *pa;
    guint i;
    gboolean ok;
    FILE *fh;
    gchar *cfgdir;

    cfgdir = g_path_get_dirname(filename);
    ok = create_config_dir_real(cfgdir, error);
    g_free(cfgdir);
    if (!ok)
        return FALSE;

    gwy_debug("Saving text settings to `%s'", filename);
    settings = gwy_app_settings_get();
    gwy_app_settings_gather(settings);
    g_return_val_if_fail(GWY_IS_CONTAINER(settings), FALSE);
    fh = g_fopen(filename, "w");
    if (!fh) {
        g_set_error(error,
                    GWY_APP_SETTINGS_ERROR, GWY_APP_SETTINGS_ERROR_FILE,
                    _("Cannot open file for writing: %s."),
                    g_strerror(errno));
        return FALSE;
    }
    if (fputs(magic_header, fh) == EOF) {
        g_set_error(error,
                    GWY_APP_SETTINGS_ERROR, GWY_APP_SETTINGS_ERROR_FILE,
                    _("Cannot write to file: %s."), g_strerror(errno));
        fclose(fh);
        return FALSE;
    }

    ok = TRUE;
    pa = gwy_container_serialize_to_text(settings);
    for (i = 0; i < pa->len; i++) {
        if (fputs((gchar*)pa->pdata[i], fh) == EOF) {
            g_set_error(error,
                        GWY_APP_SETTINGS_ERROR, GWY_APP_SETTINGS_ERROR_FILE,
                        _("Cannot write to file: %s."), g_strerror(errno));
            while (i < pa->len)
                g_free(pa->pdata[i]);
            ok = FALSE;
            break;
        }
        fputc('\n', fh);
        g_free(pa->pdata[i]);
    }
    g_ptr_array_free(pa, TRUE);
    fclose(fh);

    return ok;
}
