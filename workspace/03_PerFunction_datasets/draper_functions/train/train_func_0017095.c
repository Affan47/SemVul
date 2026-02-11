fritzfonWriteBook( void ) {
	struct sUrlHandler *psHandler;
	gchar anBuffer[ 1024 ];
	gint nError = -1;
	xmlnode *node;
	char *pnData;

	if ( routerLogin( getActiveProfile() ) == -1 ) {
		return -1;
	}

	node = phonebooksToXmlnode();

	pnData = xmlnode_to_formatted_str( node, NULL );
	if ( pnData != NULL ) {
		gchar *pnFile;

		pnFile = getBookFile();
		saveData( pnFile, pnData, -1 );

		struct curl_httppost* post = NULL;
		struct curl_httppost* last = NULL;
		struct curl_slist *m_headerlist = NULL;


		snprintf( anBuffer, sizeof( anBuffer ), "%s/cgi-bin/firmwarecfg", routerGetHost( getActiveProfile() ) );
		psHandler = urlHandler( anBuffer, 80 );

		m_headerlist = curl_slist_append(m_headerlist, "ENCTYPE=\"multipart/form-data\"");

		curl_easy_setopt(psHandler -> psHandle, CURLOPT_HTTPHEADER, m_headerlist);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "sid",   CURLFORM_COPYCONTENTS, getActiveProfile() -> sRouterInfo.pnSessionId, CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "PhonebookId",   CURLFORM_COPYCONTENTS, "0", CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "PhonebookImportFile", CURLFORM_FILE, pnFile, CURLFORM_END);

		curl_easy_setopt(psHandler -> psHandle, CURLOPT_HTTPPOST, post);

		nError = readUrl( psHandler, getActiveProfile() );
		freeHandler( psHandler );
		g_free(pnData);
		g_free( pnFile );
	}
	xmlnode_free(node);

	routerLogout( getActiveProfile() );

	return nError;
}
