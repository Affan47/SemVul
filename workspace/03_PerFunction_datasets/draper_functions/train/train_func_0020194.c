gsb_string_is_trouve ( const gchar *payee_name, const gchar *needle )
{
    gchar **tab_str;
    gchar *tmpstr;
    gint i;
    gboolean is_prefix = FALSE, is_suffix = FALSE;

    if ( g_strstr_len ( needle, -1, "%" ) == NULL &&
                        g_strstr_len ( needle, -1, "*" ) == NULL )
    {
        if ( my_strcasecmp ( payee_name, needle ) == 0 )
            return TRUE;
        else
            return FALSE;
    }
    if ( g_str_has_prefix ( needle, "%" ) == FALSE &&
                        g_str_has_prefix ( needle, "*" ) == FALSE )
        is_prefix = TRUE;

    if ( g_str_has_suffix ( needle, "%" ) == FALSE &&
                        g_str_has_suffix ( needle, "*" ) == FALSE )
        is_suffix = TRUE;

    if ( is_prefix && is_suffix )
    {
        tab_str = g_strsplit_set ( needle, "%*", 0 );
        is_prefix = g_str_has_prefix ( payee_name, tab_str[0] );
        is_suffix = g_str_has_suffix ( payee_name, tab_str[1] );
        if ( is_prefix && is_suffix )
            return TRUE;
        else
            return FALSE;
    }
    else if ( is_prefix && ! is_suffix )
    {
        tmpstr = gsb_string_supprime_joker ( needle );
        is_prefix = g_str_has_prefix (payee_name, tmpstr);
        g_free (tmpstr);
        return is_prefix;
    }
    else if ( is_suffix && ! is_prefix )
    {
        tmpstr = gsb_string_supprime_joker ( needle );
        is_suffix = g_str_has_suffix (payee_name, tmpstr);
        g_free (tmpstr);
        return is_suffix;
    }

    tab_str = g_strsplit_set ( needle, "%*", 0 );

    for (i = 0; tab_str[i] != NULL; i++)
	{
        if ( tab_str[i] && strlen (tab_str[i]) > 0)
        {
            if ( g_strstr_len (payee_name, -1, tab_str[i]))
            {
                g_strfreev ( tab_str );
                return TRUE;
            }
        }
    }

    g_strfreev ( tab_str );

    return FALSE;
}
