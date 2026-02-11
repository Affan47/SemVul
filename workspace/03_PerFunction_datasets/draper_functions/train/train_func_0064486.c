debug_message_string ( gchar *prefixe,
                        gchar *file,
                        gint line,
                        const char *function,
                        const gchar *message,
                        gint level,
                        gboolean force_debug_display )
{

    if ( ( debugging_grisbi && level <= debugging_grisbi) || force_debug_display || etat.debug_mode )
    {
        gchar* tmp_str;


        if (message)
            tmp_str = g_strdup_printf(_("%s, %2f : %s - %s:%d:%s - %s\n"),
                        get_debug_time (), (double )clock()/ CLOCKS_PER_SEC, prefixe,
                        file, line, function, message);
        else
            tmp_str = g_strdup_printf(_("%s, %2f : %s - %s:%d:%s\n"),
                        get_debug_time (), (double )clock()/ CLOCKS_PER_SEC, prefixe,
                        file, line, function);

        if ( etat.debug_mode )
        {
            fwrite ( tmp_str, sizeof (gchar), strlen ( tmp_str ), debug_file );
            fflush ( debug_file );
        }

        g_print( "%s", tmp_str );
        g_free ( tmp_str );
    }
}
