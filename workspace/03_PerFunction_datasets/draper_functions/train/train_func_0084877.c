gwyfile_save(GwyContainer *data,
             const gchar *filename,
             G_GNUC_UNUSED GwyRunType mode,
             GError **error)
{
    GByteArray *buffer;
    gchar *filename_orig_utf8, *filename_utf8;
    FILE *fh;
    gboolean restore_filename, ok = TRUE;

    if (!(fh = g_fopen(filename, "wb"))) {
        err_OPEN_WRITE(error);
        return FALSE;
    }


    restore_filename = TRUE;
    filename_orig_utf8 = NULL;
    gwy_container_gis_string_by_name(data, "/filename",
                                     (const guchar**)&filename_orig_utf8);
    filename_orig_utf8 = g_strdup(filename_orig_utf8);

    filename_utf8 = g_filename_to_utf8(filename, -1, NULL, NULL, NULL);
    if (!filename_utf8)
        gwy_container_remove_by_name(data, "/filename");
    else if (filename_orig_utf8
             && gwy_strequal(filename_orig_utf8, filename_utf8)) {
        restore_filename = FALSE;
    }
    else {
        gwy_container_set_string_by_name(data, "/filename", filename_utf8);
        filename_utf8 = NULL;
    }


    buffer = gwy_serializable_serialize(G_OBJECT(data), NULL);
    if (fwrite(MAGIC2, 1, MAGIC_SIZE, fh) != MAGIC_SIZE
        || fwrite(buffer->data, 1, buffer->len, fh) != buffer->len) {
        err_WRITE(error);
        ok = FALSE;
        g_unlink(filename);
    }
    fclose(fh);
    g_byte_array_free(buffer, TRUE);


    if (!ok && restore_filename) {
        if (filename_orig_utf8)
            gwy_container_set_string_by_name(data, "/filename",
                                             filename_orig_utf8);
        else
            gwy_container_remove_by_name(data, "/filename");
        filename_orig_utf8 = NULL;
    }
    g_free(filename_orig_utf8);
    g_free(filename_utf8);

    return ok;
}
