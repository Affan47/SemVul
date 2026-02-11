convert_filenames (void)
{
    if (! options.filenames)
        return NULL;

    Index * filenames = index_new ();
    char * * f = options.filenames;
    char * cur = g_get_current_dir ();

    for (int i = 0; f[i]; i ++)
    {
        char * uri = NULL;

        if (strstr (f[i], "://"))
            uri = str_get (f[i]);
        else if (g_path_is_absolute (f[i]))
        {
            char * tmp = filename_to_uri (f[i]);
            uri = str_get (tmp);
            free (tmp);
        }
        else
        {
            char * tmp = g_build_filename (cur, f[i], NULL);
            char * tmp2 = filename_to_uri (tmp);
            uri = str_get (tmp2);
            free (tmp);
            free (tmp2);
        }

        if (uri)
            index_append (filenames, uri);
    }

    g_free (cur);
    return filenames;
}
