gw_str_replace_str ( gchar *pattern, gchar *src, gchar *dst)
{
	gint srclen = 0, dstlen = 0;
	gchar *p, *q, *qq, *pp;
	gchar *result = NULL;
	gint nb = 0;


#ifdef GW_DEBUG_TOOLS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pattern != NULL )
	{

		q = pattern;
		while ( (q = strstr ( q, src)) != NULL )
		{
			nb++;
			q++;
		}


		if ( nb != 0 ) {

			srclen = strlen ( src);
			dstlen = strlen ( dst);
			if ( (result = (gchar *)g_malloc ( strlen ( pattern) + (nb * (dstlen - srclen)) + 1)) != NULL )
			{
				qq = result;
				q = pattern;


				while ( (p = strstr ( q, src)) != NULL )
				{
					pp = qq + (p - q);
					memcpy ( qq, q, p - q);
					memcpy ( pp, dst, dstlen);
					q = p + srclen;
					qq = pp + dstlen;
				}

				memcpy ( qq, q, strlen ( pattern) - (q - pattern));
				*((qq + strlen ( pattern)) - (q - pattern)) = '\0';
			}
		}
	}

	return result;
}
