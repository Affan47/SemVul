CodePoint_from_UTF16Nat_Surrogate ( const UTF16Unit * utf16In, const size_t utf16Len, UTF32Unit * cpOut, size_t * utf16Read )
{
	UTF16Unit hiUnit = *utf16In;
	size_t    unitCount = 0;
	UTF16Unit loUnit;
	UTF32Unit cp;


	if ( hiUnit > 0xDBFF ) UC_Throw ( "Bad UTF-16 - leading low surrogate", kXMPErr_BadParam );
	if ( utf16Len < 2 ) goto Done;

	loUnit  = *(utf16In+1);
	if ( (loUnit < 0xDC00) || (0xDFFF < loUnit) ) UC_Throw ( "Bad UTF-16 - missing low surrogate", kXMPErr_BadParam );

	unitCount = 2;
	cp = (((hiUnit & 0x3FF) << 10) | (loUnit & 0x3FF)) + 0x10000;

	*cpOut = cp;

Done:
	*utf16Read = unitCount;
	return;

}
