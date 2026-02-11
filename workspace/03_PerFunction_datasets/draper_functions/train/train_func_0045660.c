gwy_file_get_contents(const gchar *filename,
                      guchar **buffer,
                      gsize *size,
                      GError **error)
{
    GMappedFile *mfile;

    mfile = g_mapped_file_new(filename, FALSE, error);
    if (!mfile) {
        *buffer = NULL;
        *size = 0;
        return FALSE;
    }

    *buffer = g_mapped_file_get_contents(mfile);
    *size = g_mapped_file_get_length(mfile);
    if (!mapped_files)
        mapped_files = g_hash_table_new(g_direct_hash, g_direct_equal);

    if (g_hash_table_lookup(mapped_files, *buffer)) {
        g_warning("File `%s' was mapped to address %p where we already have "
                  "mapped a file.  One of the files will leak.",
                  filename, buffer);
    }
    g_hash_table_insert(mapped_files, *buffer, mfile);

    return TRUE;
}
