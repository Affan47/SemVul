toUTF8_16	(pANTLR3_STRING string)
{

	UTF8				* outputEnd;
	UTF16				* inputEnd;
	pANTLR3_STRING		utf8String;

	ConversionResult	cResult;


	utf8String	= string->factory->newStr8(string->factory, (pANTLR3_UINT8)"");

	if	(utf8String != NULL)
	{


		ANTLR3_FREE(utf8String->chars);


		utf8String->size	= string->len *3;
		utf8String->chars	= (pANTLR3_UINT8)ANTLR3_MALLOC(utf8String->size +1);

		if	(utf8String->chars != NULL)
		{
			inputEnd  = (UTF16 *)	(string->chars);
			outputEnd = (UTF8 *)	(utf8String->chars);


			cResult =  ConvertUTF16toUTF8
							(
								(const UTF16**)&inputEnd,
								((const UTF16 *)(string->chars)) + string->len,
								&outputEnd,
								outputEnd + utf8String->size - 1,
								lenientConversion
							);


			utf8String->len = ANTLR3_UINT32_CAST(((pANTLR3_UINT8)outputEnd) - utf8String->chars);

			*(outputEnd+1) = '\0';
		}
	}
	return utf8String;
}
