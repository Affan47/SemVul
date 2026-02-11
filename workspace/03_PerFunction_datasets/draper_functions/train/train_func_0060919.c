fritzfonReadBook( void ) {
	struct sUrlHandler *psHandler;
	gchar anBuffer[ 1024 ];
	gint nError = -1;
	xmlnode *psNode = NULL;
	xmlnode *psChild;
	struct curl_httppost* post = NULL;
	struct curl_httppost* last = NULL;
	struct curl_slist *m_headerlist = NULL;

	if ( routerLogin( getActiveProfile() ) == -1 ) {
		return -1;
	}

	snprintf( anBuffer, sizeof( anBuffer ), "%s/cgi-bin/firmwarecfg", routerGetHost( getActiveProfile() ) );
	psHandler = urlHandler( anBuffer, 80 );

	m_headerlist = curl_slist_append(m_headerlist, "ENCTYPE=\"multipart/form-data\"");
	curl_easy_setopt(psHandler -> psHandle, CURLOPT_HTTPHEADER, m_headerlist);

	curl_formadd(&post, &last, CURLFORM_COPYNAME, "sid",   CURLFORM_COPYCONTENTS, getActiveProfile() -> sRouterInfo.pnSessionId, CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "PhonebookId",   CURLFORM_COPYCONTENTS, "0", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "PhonebookExportName",   CURLFORM_COPYCONTENTS, "Telefonbuch", CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "PhonebookExport",   CURLFORM_COPYCONTENTS, "", CURLFORM_END);

	curl_easy_setopt(psHandler -> psHandle, CURLOPT_HTTPPOST, post);


	nError = readUrl( psHandler, getActiveProfile() );
	if ( nError == 0 ) {
		gchar *pnFile;

		pnFile = getBookFile();
		saveData( pnFile, psHandler -> pnData, psHandler -> nSize );

		psNode = readXmlFromFile( pnFile, "phonebooks" );
		if ( psNode == NULL ) {
			Debug( KERN_DEBUG, "Could not read %s\n", pnFile );
			g_free( pnFile );
			freeHandler( psHandler );
			return -1;
		}
		g_free( pnFile );

		for ( psChild = xmlnode_get_child( psNode, "phonebook" ); psChild != NULL; psChild = xmlnode_get_next_twin( psChild ) ) {
			addPhonebook( psChild );
		}
	}
	freeHandler( psHandler );

	routerLogout( getActiveProfile() );

	return 0;
}
