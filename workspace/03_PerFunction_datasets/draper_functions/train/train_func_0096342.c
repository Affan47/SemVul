sis_load(const gchar *filename,
         G_GNUC_UNUSED GwyRunType mode,
         GError **error)
{
    guchar *buffer;
    gsize size;
    GError *err = NULL;
    GwyDataField *dfield = NULL;
    GwyContainer *data = NULL;
    SISFile sisfile;
    SISImage *image;
    GString *key;
    const gchar *s;
    guint n;
    guint i, j;

    if (!gwy_file_get_contents(filename, &buffer, &size, &err)) {
        err_GET_FILE_CONTENTS(error, &err);
        return NULL;
    }
    n = 0;
    gwy_clear(&sisfile, 1);
    sisfile.params = g_hash_table_new_full(g_direct_hash, g_direct_equal,
                                           NULL, g_free);
    if (sis_real_load(buffer, size, &sisfile, error)) {
        data = gwy_container_new();
        key = g_string_new(NULL);
        for (i = 0; i < sisfile.nchannels; i++) {
            for (j = 0; j < sisfile.channels[i].nimages; j++) {
                image = sisfile.channels[i].images + j;
                if (!image->image_data)
                    continue;

                dfield = extract_data(&sisfile, i, j, &err);
                if (dfield) {
                    g_clear_error(&err);
                    g_string_printf(key, "/%u/data", n);
                    gwy_container_set_object_by_name(data, key->str, dfield);
                    g_object_unref(dfield);
                    g_string_append(key, "/title");
                    s = gwy_enuml_to_string(sisfile.channels[i].data_type,
                                            "Topography", 1,
                                            "Field Contrast", 2,
                                            "Error", 3,
                                            "Exterm", 4,
                                            "Loc", 5,
                                            "Phase", 6,
                                            "Capacity", 7,
                                            "Amplitude", 8,
                                            "Frequency", 9,
                                            "Potential", 10,
                                            "Friction", 11,
                                            "Force Modulation (FMM)", 12,
                                            "User", 13,
                                            NULL);
                    if (s)
                        gwy_container_set_string_by_name(data, key->str,
                                                         g_strdup(s));
                    add_metadata(&sisfile, n, i, data);
                    n++;
                }
            }
        }
        g_string_free(key, TRUE);

        if (!n) {
            if (err)
                g_propagate_error(error, err);
            else
                err_NO_DATA(error);
            gwy_object_unref(data);
        }
    }

    gwy_file_abandon_contents(buffer, size, NULL);
    g_hash_table_destroy(sisfile.params);
    for (i = 0; i < sisfile.nchannels; i++)
        g_free(sisfile.channels[i].images);
    g_free(sisfile.channels);

    return data;
}
