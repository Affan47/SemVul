ComposeLangSelector ( XMP_StringPtr	schemaNS,
								XMP_StringPtr	arrayName,
								XMP_StringPtr	_langName,
								XMP_VarString * _fullPath )
{
	XMP_Assert ( schemaNS != 0 );
	XMP_Assert ( (arrayName != 0) && (*arrayName != 0) );
	XMP_Assert ( (_langName != 0) && (*_langName != 0) );
	XMP_Assert ( _fullPath != 0 );

	XMP_ExpandedXPath expPath;
	ExpandXPath ( schemaNS, arrayName, &expPath );

	XMP_VarString langName ( _langName );
	NormalizeLangValue ( &langName );

	XMP_StringLen reserveLen = strlen(arrayName) + langName.size() + 14;

	XMP_VarString fullPath;
	fullPath.reserve ( reserveLen );
	fullPath = arrayName;
	fullPath += "[?xml:lang=\"";
	fullPath += langName;
	fullPath += "\"]";

	*_fullPath = fullPath;

}
