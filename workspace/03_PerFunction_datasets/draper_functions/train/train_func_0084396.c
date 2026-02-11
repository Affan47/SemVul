spmlab_load(const gchar *filename,
            G_GNUC_UNUSED GwyRunType mode,
            GError **error)
{
    GwyContainer *container = NULL;
    guchar *buffer = NULL;
    gsize size = 0;
    GError *err = NULL;
    GwyDataField *dfield = NULL;
    gchar *title = NULL;
    gint dir;

    if (!gwy_file_get_contents(filename, &buffer, &size, &err)) {
        err_GET_FILE_CONTENTS(error, &err);
        return NULL;
    }


    if (size < 2048) {
        err_TOO_SHORT(error);
        gwy_file_abandon_contents(buffer, size, NULL);
        return NULL;
    }
    if (buffer[0] != '#' || buffer[1] != 'R') {
        err_FILE_TYPE(error, "Thermicroscopes SpmLab");
        gwy_file_abandon_contents(buffer, size, NULL);
        return NULL;
    }
    switch (buffer[2]) {
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        dfield = read_data_field(buffer, size, buffer[2], &title, &dir, error);
        break;

        default:
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("Unknown format version %c."), buffer[2]);
        break;
    }

    gwy_file_abandon_contents(buffer, size, NULL);
    if (!dfield)
        return NULL;

    container = gwy_container_new();
    gwy_container_set_object_by_name(container, "/0/data", dfield);
    g_object_unref(dfield);

    if (title)
        gwy_container_set_string_by_name(container, "/0/data/title", title);
    else
        gwy_app_channel_title_fall_back(container, 0);


    return container;
}
