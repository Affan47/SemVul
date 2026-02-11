IsASCII ( const void * textPtr, size_t textLen )
{

	for ( const XMP_Uns8 * textPos = (XMP_Uns8*)textPtr; textLen > 0; --textLen, ++textPos ) {
		if ( *textPos >= 0x80 ) return false;
	}

	return true;

}
