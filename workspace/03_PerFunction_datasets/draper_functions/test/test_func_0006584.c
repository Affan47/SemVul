UTF16Nat_to_UTF32Nat ( const UTF16Unit * utf16In,   const size_t utf16Len,
				                   UTF32Unit *       utf32Out,  const size_t utf32Len,
				                   size_t *          utf16Read, size_t *     utf32Written )
{
	const UTF16Unit * utf16Pos = utf16In;
	UTF32Unit *       utf32Pos = utf32Out;

	size_t utf16Left = utf16Len;
	size_t utf32Left = utf32Len;

	UC_Assert ( (utf16In != 0) && (utf32Out != 0) && (utf16Read != 0) && (utf32Written != 0) );

	while ( (utf16Left > 0) && (utf32Left > 0) ) {


		size_t i, limit = utf16Left;
		if ( limit > utf32Left ) limit = utf32Left;
		for ( i = 0; i < limit; ++i ) {
			UTF16Unit inUnit = *utf16Pos;
			if ( (0xD800 <= inUnit) && (inUnit <= 0xDFFF) ) break;
			*utf32Pos = inUnit;
			++utf16Pos;
			++utf32Pos;
		}
		utf16Left -= i;
		utf32Left -= i;


		while ( (utf16Left > 0) && (utf32Left > 0) ) {
			size_t len;
			UTF16Unit inUnit = *utf16Pos;
			if ( (inUnit < 0xD800) || (0xDFFF < inUnit) ) break;
			CodePoint_from_UTF16Nat_Surrogate ( utf16Pos, utf16Left, utf32Pos, &len );
			if ( len == 0 ) goto Done;
			UC_Assert ( len == 2 );
			utf16Left -= len;
			utf16Pos  += len;
			utf32Left -= 1;
			utf32Pos  += 1;
		}

	}

Done:
	*utf16Read = utf16Len - utf16Left;
	*utf32Written = utf32Len - utf32Left;

}
