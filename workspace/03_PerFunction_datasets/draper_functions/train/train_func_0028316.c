read_result_file( gchar *filename )
{
    gchar *utf8     = NULL;
    gchar *contents = NULL;
    GError *error   = NULL ;
    if (g_file_get_contents(filename, &contents, NULL, &error ))
    {
        if ( contents )
        {
            utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
            GMS_G_FREE(contents);
        }
    }
    return utf8 ;
}
