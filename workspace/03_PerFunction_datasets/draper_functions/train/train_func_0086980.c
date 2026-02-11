gw_str_blob_to_regex ( gchar *blob)
{

	gchar *regex = NULL;
	gchar *convert_table_in[17] = {"\\", ".", "*", "?", "^", "$", "|", "(", ")", "[", "]", "{", "{", "+", "?", ",", NULL};
	gchar *convert_table_out[17] = {"\\\\","\\.",".*",".","\\^","\\$","\\|","\\(","\\)","\\[","\\[","\\}","\\}","\\+","\\?","\\,", NULL};


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( blob != NULL )
	{
		if ( ( regex = gw_str_replace_strv ( blob, convert_table_in, convert_table_out)) == NULL )
		{
			regex = g_strdup ( blob);
		}
	}

	return regex;
}
