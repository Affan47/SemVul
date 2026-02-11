inpname_exists (const gchar *inppath, const gchar *inpname)
{
        gchar *inpfile;
        gchar *filename;
        gboolean exists;


        inpfile = g_strdup_printf ("%s", inpname);
        filename = g_build_filename (inppath, inpfile, NULL);
        exists = g_file_test (filename, G_FILE_TEST_EXISTS);
        g_free (filename);
        g_free (inpfile);

        if (exists)
                return TRUE;

        inpfile = g_strdup_printf ("%s.inp", inpname);
        filename = g_build_filename (inppath, inpfile, NULL);
        exists = g_file_test (filename, G_FILE_TEST_EXISTS);
        g_free (filename);
        g_free (inpfile);

        return exists;
}
