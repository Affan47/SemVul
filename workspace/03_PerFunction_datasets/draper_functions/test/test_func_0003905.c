RegisterNamespace ( XMP_StringPtr	 namespaceURI,
                             XMP_StringPtr	 prefix )
{
	if ( (*namespaceURI == 0) || (*prefix == 0) ) {
		XMP_Throw ( "Empty namespace URI or prefix", kXMPErr_BadParam );
	}

	XMP_VarString	nsURI ( namespaceURI );
	XMP_VarString	prfix ( prefix );
	if ( prfix[prfix.size()-1] != ':' ) prfix += ':';
	VerifySimpleXMLName ( prefix, prefix+prfix.size()-1 );


        (*sNamespaceURIToPrefixMap)[nsURI] = prfix;
        (*sNamespacePrefixToURIMap)[prfix] = nsURI;

}
