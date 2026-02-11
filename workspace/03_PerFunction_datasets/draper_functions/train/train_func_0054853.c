RDF_PropertyElement ( XMP_Node * xmpParent, const XML_Node & xmlNode, bool isTopLevel )
{
	RDFTermKind nodeTerm = GetRDFTermKind ( xmlNode.name );
	if ( ! IsPropertyElementName ( nodeTerm ) ) XMP_Throw ( "Invalid property element name", kXMPErr_BadRDF );

	if ( xmlNode.attrs.size() > 3 ) {


		RDF_EmptyPropertyElement ( xmpParent, xmlNode, isTopLevel );

	} else {


		XML_cNodePos currAttr = xmlNode.attrs.begin();
		XML_cNodePos endAttr  = xmlNode.attrs.end();
		XMP_VarString * attrName = 0;

		for ( ; currAttr != endAttr; ++currAttr ) {
			attrName = &((*currAttr)->name);
			if ( (*attrName != "xml:lang") && (*attrName != "rdf:ID") ) break;
		}

		if ( currAttr != endAttr ) {

			XMP_Assert ( attrName != 0 );
			XMP_VarString& attrValue = (*currAttr)->value;

			if ( *attrName == "rdf:datatype" ) {
				RDF_LiteralPropertyElement ( xmpParent, xmlNode, isTopLevel );
			} else if ( *attrName != "rdf:parseType" ) {
				RDF_EmptyPropertyElement ( xmpParent, xmlNode, isTopLevel );
			} else if ( attrValue == "Literal" ) {
				RDF_ParseTypeLiteralPropertyElement ( xmpParent, xmlNode, isTopLevel );
			} else if ( attrValue == "Resource" ) {
				RDF_ParseTypeResourcePropertyElement ( xmpParent, xmlNode, isTopLevel );
			} else if ( attrValue == "Collection" ) {
				RDF_ParseTypeCollectionPropertyElement ( xmpParent, xmlNode, isTopLevel );
			} else {
				RDF_ParseTypeOtherPropertyElement ( xmpParent, xmlNode, isTopLevel );
			}

		} else {


			if ( xmlNode.content.empty() ) {

				RDF_EmptyPropertyElement ( xmpParent, xmlNode, isTopLevel );

			} else {

				XML_cNodePos currChild = xmlNode.content.begin();
				XML_cNodePos endChild  = xmlNode.content.end();

				for ( ; currChild != endChild; ++currChild ) {
					if ( (*currChild)->kind != kCDataNode ) break;
				}

				if ( currChild == endChild ) {
					RDF_LiteralPropertyElement ( xmpParent, xmlNode, isTopLevel );
				} else {
					RDF_ResourcePropertyElement ( xmpParent, xmlNode, isTopLevel );
				}

			}

		}

	}

}
