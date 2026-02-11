gwy_calibration_parse(const gchar *text,
                      G_GNUC_UNUSED gboolean is_const)
{
    GwyCalibration *calibration = NULL;
    GwyCalibrationClass *klass;
    G_GNUC_UNUSED guint ndata = 0;
    gchar *str, *p, *line, *key, *filename=NULL, *value;

    g_return_val_if_fail(text, NULL);
    klass = g_type_class_peek(GWY_TYPE_CALIBRATION);
    g_return_val_if_fail(klass, NULL);

    p = str = g_strdup(text);

    while ((line = gwy_str_next_line(&p))) {
        g_strstrip(line);
        key = line;
        if (!*key)
            continue;
        value = strchr(key, ' ');
        if (value) {
            *value = '\0';
            value++;
            g_strstrip(value);
        }
        if (!value || !*value) {
            g_warning("Missing value for `%s'.", key);
            continue;
        }


        if (gwy_strequal(key, "npoints"))
            ndata = atoi(value);
        else if (gwy_strequal(key, "filename")) {
            filename = strdup(value);
        }
        else
            g_warning("Unknown field `%s'.", key);
    }

    calibration = gwy_calibration_new(filename, filename);
    gwy_calibration_sanitize(calibration);
    return (GwyResource*)calibration;
}
