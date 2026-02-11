gw_str_key_words_to_regex ( gchar *key_words)
{
	gchar **words = NULL;
	gchar *regex_build = NULL;
	int i = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( key_words != NULL )
	{
		gw_strdel_chrsry ( key_words, ' ');
		gw_str_trim ( key_words);
		words = g_strsplit ( key_words, " ", 0);

		if ( words != NULL )
		{
			for ( i = 0; words[i] != NULL; i++)
			{
				regex_build = g_strconcat ( ".*", words[i], ".*", NULL);
				g_free ( words[i]);
				words[i] = regex_build;
#ifdef GW_DEBUG_TOOLS_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : an new pattern search is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, words[i]);
#endif
			}
		}
	}

	return words;
}
