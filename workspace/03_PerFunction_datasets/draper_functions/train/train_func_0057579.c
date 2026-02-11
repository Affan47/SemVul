program_exist (const gchar *program)
{
    gchar *path;
    gboolean found = FALSE;

    path = g_find_program_in_path(program);
    if (path) {
        found = TRUE;
        g_free(path);
    }
    return found;
}
