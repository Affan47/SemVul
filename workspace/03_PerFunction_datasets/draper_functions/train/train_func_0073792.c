VerifyQualName ( XMP_StringPtr qualName, XMP_StringPtr nameEnd )
{
	if ( qualName >= nameEnd ) XMP_Throw ( "Empty qualified name", kXMPErr_BadXPath );

	XMP_StringPtr colonPos = qualName;
	while ( (colonPos < nameEnd) && (*colonPos != ':') ) ++colonPos;
	if ( (colonPos == qualName) || (colonPos >= nameEnd) ) XMP_Throw ( "Ill-formed qualified name", kXMPErr_BadXPath );

	VerifySimpleXMLName ( qualName, colonPos );
	VerifySimpleXMLName ( colonPos+1, nameEnd );

	size_t prefixLen = colonPos - qualName + 1;
	XMP_VarString prefix ( qualName, prefixLen );
	XMP_StringMapPos prefixPos = sNamespacePrefixToURIMap->find ( prefix );
	if ( prefixPos == sNamespacePrefixToURIMap->end() ) {
		XMP_Throw ( "Unknown namespace prefix for qualified name", kXMPErr_BadXPath );
	}

}
