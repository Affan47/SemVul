gl_recent_get_utf8_filename (GtkRecentInfo *item)
{
        const gchar *uri;
        gchar       *filename;
        gchar       *utf8_filename = NULL;

        gl_debug (DEBUG_RECENT, "START");

        uri = gtk_recent_info_get_uri (item);

        filename = g_filename_from_uri (uri, NULL, NULL);
        if ( filename != NULL )
        {
                utf8_filename = g_filename_to_utf8 (filename, -1, NULL, NULL, NULL);
                g_free (filename);
        }

        return utf8_filename;
        gl_debug (DEBUG_RECENT, "END");
}
