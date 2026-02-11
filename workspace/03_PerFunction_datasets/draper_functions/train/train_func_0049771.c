gwyfile_load(const gchar *filename,
             G_GNUC_UNUSED GwyRunType mode,
             GError **error)
{
    GObject *object;
    GError *err = NULL;
    guchar *buffer = NULL;
    gsize size = 0;
    gsize pos = 0;

    if (!gwy_file_get_contents(filename, &buffer, &size, &err)) {
        err_GET_FILE_CONTENTS(error, &err);
        return NULL;
    }
    if (size < MAGIC_SIZE
        || (memcmp(buffer, MAGIC, MAGIC_SIZE)
            && memcmp(buffer, MAGIC2, MAGIC_SIZE))) {
        err_FILE_TYPE(error, "Gwyddion");
        gwy_file_abandon_contents(buffer, size, &err);
        return NULL;
    }

    if (!memcmp(buffer, MAGIC, MAGIC_SIZE)) {
        object = gwy_container_deserialize_old(buffer + MAGIC_SIZE,
                                               size - MAGIC_SIZE, &pos);
        gwyfile_remove_old_data(object);
    }
    else
        object = gwy_serializable_deserialize(buffer + MAGIC_SIZE,
                                              size - MAGIC_SIZE, &pos);

    gwy_file_abandon_contents(buffer, size, &err);
    if (!object) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("Data deserialization failed."));
        return NULL;
    }
    if (!GWY_IS_CONTAINER(object)) {
        g_set_error(error, GWY_MODULE_FILE_ERROR, GWY_MODULE_FILE_ERROR_DATA,
                    _("Data deserialization succeeded, but resulted in "
                      "an unexpected object %s."),
                    g_type_name(G_TYPE_FROM_INSTANCE(object)));
        g_object_unref(object);
        return NULL;
    }
    gwyfile_pack_metadata(GWY_CONTAINER(object));

    return GWY_CONTAINER(object);
}
