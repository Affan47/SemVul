unisoku_load(const gchar *filename,
             G_GNUC_UNUSED GwyRunType mode,
             GError **error)
{
    UnisokuFile ufile;
    GwyContainer *meta, *container = NULL;
    guchar *buffer = NULL;
    gchar *text = NULL;
    gsize i, size = 0;
    GError *err = NULL;
    GwyDataField *dfield = NULL;
    gchar *data_name;

    if (!g_file_get_contents(filename, &text, &size, &err)) {
        err_GET_FILE_CONTENTS(error, &err);
        return NULL;
    }

    for (i = 0; i < size; i++) {
        if (!text[i])
            text[i] = ' ';
    }

    gwy_clear(&ufile, 1);
    if (!unisoku_read_header(text, &ufile, error)) {
        unisoku_file_free(&ufile);
        g_free(text);
        return NULL;
    }
    g_free(text);

    if (ufile.data_type < UNISOKU_UINT8
        || ufile.data_type > UNISOKU_FLOAT
        || type_sizes[ufile.data_type] == 0) {
        err_DATA_TYPE(error, ufile.data_type);
        unisoku_file_free(&ufile);
        return NULL;
    }

    if (!(data_name = unisoku_find_data_name(filename))) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("No corresponding data file was found for header file."));
        unisoku_file_free(&ufile);
        return NULL;
    }

    if (!gwy_file_get_contents(data_name, &buffer, &size, &err)) {
        err_GET_FILE_CONTENTS(error, &err);
        unisoku_file_free(&ufile);
        return NULL;
    }

    dfield = unisoku_read_data_field(buffer, size, &ufile, error);
    gwy_file_abandon_contents(buffer, size, NULL);

    if (!dfield) {
        unisoku_file_free(&ufile);
        return NULL;
    }

    container = gwy_container_new();
    gwy_container_set_object_by_name(container, "/0/data", dfield);
    g_object_unref(dfield);
    gwy_app_channel_title_fall_back(container, 0);

    meta = unisoku_get_metadata(&ufile);
    gwy_container_set_object_by_name(container, "/0/meta", meta);
    g_object_unref(meta);

    unisoku_file_free(&ufile);

    return container;
}
