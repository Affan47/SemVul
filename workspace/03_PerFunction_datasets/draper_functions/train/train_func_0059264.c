vcard_read_qp( VCardFile *cardFile, char *tagvalue ) {
	GSList *listQP = NULL;
	gint len = 0;
	gchar *line = tagvalue;
	while( line ) {
		listQP = g_slist_append( listQP, line );
		len = strlen( line ) - 1;
		if( line[ len ] != '=' ) break;
		line[ len ] = '\0';
		line = vcard_get_line( cardFile );
	}


	line = mgu_list_coalesce( listQP );


	mgu_free_list( listQP );
	listQP = NULL;
	return line;
}
