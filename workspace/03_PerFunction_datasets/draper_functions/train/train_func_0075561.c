addrharvest_check_hdr( GList *listHdr, gchar *buf ) {
	gboolean retVal;
	GList *node;
	gchar *p, *hdr, *nhdr;
	gint len;

	retVal = FALSE;
	p = strchr( buf, ':' );
	if( p ) {
		len = ( size_t ) ( p - buf );
		hdr = g_strndup( buf, len );
		node = listHdr;
		while( node ) {
			nhdr = node->data;
			if (g_ascii_strncasecmp(nhdr, hdr, strlen(nhdr)) == 0 ) {
				retVal = TRUE;
				break;
			}
			node = g_list_next( node );
		}
		g_free( hdr );
	}
	return retVal;
}
