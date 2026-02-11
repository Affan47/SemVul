EncodeToBase64 ( XMP_StringPtr   rawStr,
						   XMP_StringLen   rawLen,
						   XMP_VarString * encodedStr )
{
	if ( (rawStr == 0) && (rawLen != 0) ) XMP_Throw ( "Null raw data buffer", kXMPErr_BadParam );
	XMP_Assert ( encodedStr != 0 );

	encodedStr->erase();
	if ( rawLen == 0 ) return;

	char	encChunk[4];

	unsigned long	in, out;
	unsigned char	c1, c2, c3;
	unsigned long	merge;

	const size_t	outputSize	= (rawLen / 3) * 4;

	encodedStr->reserve ( outputSize );


	for ( in = 0, out = 0; (in+2) < rawLen; in += 3, out += 4 ) {

		c1	= rawStr[in];
		c2	= rawStr[in+1];
		c3	= rawStr[in+2];

		merge	= (c1 << 16) + (c2 << 8) + c3;

		encChunk[0] = sBase64Chars [ merge >> 18 ];
		encChunk[1] = sBase64Chars [ (merge >> 12) & 0x3F ];
		encChunk[2] = sBase64Chars [ (merge >> 6) & 0x3F ];
		encChunk[3] = sBase64Chars [ merge & 0x3F ];

		if ( out >= 76 ) {
			encodedStr->append ( 1, kLF );
			out = 0;
		}
		encodedStr->append ( encChunk, 4 );

	}


	switch ( rawLen - in ) {

		case 0:
			break;

		case 1:

			c1	= rawStr[in];
			merge	= c1 << 16;

			encChunk[0] = sBase64Chars [ merge >> 18 ];
			encChunk[1] = sBase64Chars [ (merge >> 12) & 0x3F ];
			encChunk[2] = encChunk[3] = '=';

			if ( out >= 76 ) encodedStr->append ( 1, kLF );
			encodedStr->append ( encChunk, 4 );
			break;

		case 2:

			c1	= rawStr[in];
			c2	= rawStr[in+1];
			merge	= (c1 << 16) + (c2 << 8);

			encChunk[0] = sBase64Chars [ merge >> 18 ];
			encChunk[1] = sBase64Chars [ (merge >> 12) & 0x3F ];
			encChunk[2] = sBase64Chars [ (merge >> 6) & 0x3F ];
			encChunk[3] = '=';

			if ( out >= 76 ) encodedStr->append ( 1, kLF );
			encodedStr->append ( encChunk, 4 );
			break;

	}

}
