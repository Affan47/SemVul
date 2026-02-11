pref_to_xmlnode( xmlnode *psParent, struct sPref *psPref ) {
	xmlnode *psNode = NULL;
	struct sPref *psChild;
	char anBuf[ 20 ];

	psNode = xmlnode_new_child( psParent, "pref" );
	xmlnode_set_attrib( psNode, "name", psPref -> pnName );

	if ( psPref -> nType == PREF_STRING ) {
		xmlnode_set_attrib( psNode, "type", "string" );
		xmlnode_set_attrib( psNode, "value", psPref -> uValue.pnString ? psPref -> uValue.pnString : "" );
	} else if ( psPref -> nType == PREF_INT ) {
		xmlnode_set_attrib( psNode, "type", "int" );
		snprintf( anBuf, sizeof( anBuf ), "%d", psPref -> uValue.nInteger );
		xmlnode_set_attrib( psNode, "value", anBuf );
	} else if ( psPref -> nType == PREF_BOOLEAN ) {
		xmlnode_set_attrib( psNode, "type", "bool" );
		snprintf( anBuf, sizeof( anBuf ), "%d", psPref -> uValue.bBoolean );
		xmlnode_set_attrib( psNode, "value", anBuf );
	} else if ( psPref -> nType == PREF_PATH ) {
		gchar *pnEncoded = g_filename_to_utf8( psPref -> uValue.pnString ? psPref -> uValue.pnString : "", -1, NULL, NULL, NULL );
		xmlnode_set_attrib( psNode, "type", "path" );
		xmlnode_set_attrib( psNode, "value", pnEncoded );
		g_free( pnEncoded );
	}

	for ( psChild = psPref -> psFirstChild; psChild != NULL; psChild = psChild -> psSibling ) {
		pref_to_xmlnode( psNode, psChild );
	}
}
