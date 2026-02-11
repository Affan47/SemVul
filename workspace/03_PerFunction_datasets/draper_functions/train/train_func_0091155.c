split_per_axis_field(const gchar *value,
                     const gchar *name,
                     guint nitems,
                     gboolean quoted,
                     GError **error)
{
    gchar **raw_fields, **fields, *f;
    guint n = 0, i, len;

    raw_fields = g_strsplit_set(value, " \t\v\r\n", -1);
    fields = g_new0(gchar*, nitems+1);
    for (i = 0; (f = raw_fields[i]); i++) {
        len = strlen(f);
        if (!len)
            continue;

        if (quoted) {
            if (len < 2 || f[0] != '"' || f[len-1] != '"') {
                g_set_error(error, GWY_MODULE_FILE_ERROR,
                            GWY_MODULE_FILE_ERROR_DATA,
                            _("Items of per-axis header field %s are not "
                              "quoted."),
                            name);
                goto fail;
            }
            f[len-1] = '\0';
            f++;
        }
        if (n == nitems) {
            g_set_error(error, GWY_MODULE_FILE_ERROR,
                        GWY_MODULE_FILE_ERROR_DATA,
                        _("Per-axis header field %s contains too many "
                          "items."),
                        name);
            goto fail;
        }
        fields[n++] = g_strdup(f);
    }
    if (n < nitems) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("Per-axis header field %s contains too few items."),
                    name);
        goto fail;
    }

    g_strfreev(raw_fields);
    return fields;

fail:
    g_strfreev(raw_fields);
    g_strfreev(fields);
    return NULL;
}
