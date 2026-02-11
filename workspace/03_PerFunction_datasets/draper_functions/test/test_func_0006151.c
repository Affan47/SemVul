URLEncode(const wxString& sIn)
{
	wxString sOut;
	unsigned char curChar;

	for ( unsigned int i = 0; i < sIn.Length(); ++i ) {
		curChar = sIn.GetChar( i );

		if ( isalnum( curChar ) ) {
	        sOut += curChar;
	    } else if( isspace ( curChar ) ) {
		    sOut += wxT("+");
		} else {
			sOut += wxT("%");
			sOut += base16Chars[ curChar >> 4];
			sOut += base16Chars[ curChar & 0xf];
		}

	}

	return sOut;
}
