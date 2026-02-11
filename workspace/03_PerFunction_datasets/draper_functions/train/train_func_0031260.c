socket_filename (const char *prefix)
{
    char *pattern, *newfile, *path, *filename;
    const char *tmpdir;

    pattern = g_strdup_printf ("%s.%s.*", prefix, g_get_user_name ());
    tmpdir = g_get_tmp_dir ();
    filename = find_file_with_pattern (tmpdir, pattern);
    if (filename == NULL)
    {
        newfile = g_strdup_printf ("%s.%s.%u", prefix,
                g_get_user_name (), g_random_int ());
        path = g_build_filename (tmpdir, newfile, NULL);
        g_free (newfile);
    } else {
        path = g_build_filename (tmpdir, filename, NULL);
        g_free (filename);
    }

    g_free (pattern);
    return path;
}
