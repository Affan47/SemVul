CountControlEscape ( const XMP_Uns8 * escStart, const XMP_Uns8 * bufEnd )
{
	XMP_Assert ( escStart < bufEnd );
	if ( escStart >= bufEnd ) return 0;
	XMP_Assert ( *escStart == '&' );

	size_t tailLen = bufEnd - escStart;
	if ( tailLen < 5 ) return -1;

	if ( strncmp ( (char*)escStart, "&#x", 3 ) != 0 ) return 0;

	XMP_Uns8 escValue = 0;
	const XMP_Uns8 * escPos = escStart + 3;

	if ( ('0' <= *escPos) && (*escPos <= '9') ) {
		escValue = *escPos - '0';
		++escPos;
	} else if ( ('A' <= *escPos) && (*escPos <= 'F') ) {
		escValue = *escPos - 'A' + 10;
		++escPos;
	} else if ( ('a' <= *escPos) && (*escPos <= 'f') ) {
		escValue = *escPos - 'a' + 10;
		++escPos;
	}

	if ( ('0' <= *escPos) && (*escPos <= '9') ) {
		escValue = (escValue << 4) + (*escPos - '0');
		++escPos;
	} else if ( ('A' <= *escPos) && (*escPos <= 'F') ) {
		escValue = (escValue << 4) + (*escPos - 'A' + 10);
		++escPos;
	} else if ( ('a' <= *escPos) && (*escPos <= 'f') ) {
		escValue = (escValue << 4) + (*escPos - 'a' + 10);
		++escPos;
	}

	if ( escPos == bufEnd ) return -1;
	if ( *escPos != ';' ) return 0;

	size_t escLen = escPos - escStart + 1;
	if ( escLen < 5 ) return 0;

	if ( (escValue == kTab) || (escValue == kLF) || (escValue == kCR) ) return 0;

	return escLen;

}
