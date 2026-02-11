gw_strcmp_strregex ( gchar *str, gchar *regex, gboolean case_sensitive)
{
        regex_t *r=NULL;
	regex_t real;
        gint cflags;
        gint result = -1;
	r = &real;


#ifdef GW_DEBUG_TOOLS_COMPONENT
        g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( case_sensitive == FALSE )
	{
		cflags = REG_ICASE|REG_NOSUB;
	}
	else
	{
		cflags = 0|REG_NOSUB;
	}

	if ( regcomp ( r, regex, cflags) == 0 )
	{
		if ( regexec ( r, str, 0, NULL, 0) == 0 )
		{
			result = 0;
		}
	}

	regfree ( r);

#ifdef GW_DEBUG_TOOLS_COMPONENT
        if ( result == 0 )
        {
                g_print ( "*** GW - %s (%d) :: %s() : %s == %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str, regex);
        }
        else
        {
                g_print ( "*** GW - %s (%d) :: %s() : %s <> %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, str, regex);
        }
#endif

        return result;
}
