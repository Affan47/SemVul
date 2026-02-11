xmlnode_remove_attrib( xmlnode *psNode, const char *pnAttr ) {
	xmlnode *psAttrNode, *psSibling = NULL;

	g_return_if_fail( psNode != NULL );
	g_return_if_fail( pnAttr != NULL );

	for ( psAttrNode = psNode -> psChild; psAttrNode != NULL; psAttrNode = psAttrNode -> psNext ) {
		if ( psAttrNode -> nType == XMLNODE_TYPE_ATTRIB && !strcmp( psAttrNode -> pnName, pnAttr ) ) {
			if ( psSibling == NULL ) {
				psNode -> psChild = psAttrNode -> psNext;
			} else {
				psSibling -> psNext = psAttrNode -> psNext;
			}
			if ( psNode -> psLastChild == psAttrNode ) {
				psNode -> psLastChild = psSibling;
			}
			xmlnode_free( psAttrNode );
			return;
		}
		psSibling = psAttrNode;
	}
}
