FindFileExtension ( XMP_StringPtr filePath )
{

	XMP_StringPtr pathEnd = filePath + strlen(filePath);
	XMP_StringPtr extPtr;

	for ( extPtr = pathEnd-1; extPtr > filePath; --extPtr ) {
		if ( (*extPtr == '.') || (*extPtr == '/') ) break;
		#if XMP_WinBuild
			if ( (*extPtr == '\\') || (*extPtr == ':') ) break;
		#endif
	}

	if ( (extPtr < filePath) || (*extPtr != '.') ) return pathEnd;
	return extPtr;

}
