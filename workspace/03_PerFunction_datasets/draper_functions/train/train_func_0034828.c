VerifySetOptions ( XMP_OptionBits options, XMP_StringPtr propValue )
{

	if ( options & kXMP_PropArrayIsAltText )   options |= kXMP_PropArrayIsAlternate;
	if ( options & kXMP_PropArrayIsAlternate ) options |= kXMP_PropArrayIsOrdered;
	if ( options & kXMP_PropArrayIsOrdered )   options |= kXMP_PropValueIsArray;

	if ( options & ~kXMP_AllSetOptionsMask ) {
		XMP_Throw ( "Unrecognized option flags", kXMPErr_BadOptions );
	}

	if ( (options & kXMP_PropValueIsStruct) && (options & kXMP_PropValueIsArray) ) {
		XMP_Throw ( "IsStruct and IsArray options are mutually exclusive", kXMPErr_BadOptions );
	}

	if ( (options & kXMP_PropValueOptionsMask) && (options & kXMP_PropCompositeMask) ) {
		XMP_Throw ( "Structs and arrays can't have \"value\" options", kXMPErr_BadOptions );
	}

	if ( (propValue != 0) && (options & kXMP_PropCompositeMask) ) {
		XMP_Throw ( "Structs and arrays can't have string values", kXMPErr_BadOptions );
	}

	return options;

}
