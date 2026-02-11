SetQualifier ( XMP_StringPtr  schemaNS,
						XMP_StringPtr  propName,
						XMP_StringPtr  qualNS,
						XMP_StringPtr  qualName,
						XMP_StringPtr  qualValue,
						XMP_OptionBits options )
{
	XMP_Assert ( (schemaNS != 0) && (propName != 0) && (qualNS != 0) && (qualName != 0) );

	XMP_StringPtr	qualPath;
	XMP_StringLen	pathLen;

	XMP_ExpandedXPath expPath;
	ExpandXPath ( schemaNS, propName, &expPath );
	XMP_Node * propNode = FindNode ( &tree, expPath, kXMP_ExistingOnly );
	if ( propNode == 0 ) XMP_Throw ( "Specified property does not exist", kXMPErr_BadXPath );

	XMPUtils::ComposeQualifierPath ( schemaNS, propName, qualNS, qualName, &qualPath, &pathLen );
	SetProperty ( schemaNS, qualPath, qualValue, options );

}
