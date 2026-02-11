newPtr16_8	(pANTLR3_STRING_FACTORY factory, pANTLR3_UINT8 ptr, ANTLR3_UINT32 size)
{
	pANTLR3_STRING  string;


	string  = factory->newSize(factory, size);

	if	(string == NULL)
	{
		return	NULL;
	}

	if	(size <= 0)
	{
		return	string;
	}

	if	(ptr != NULL)
	{
		pANTLR3_UINT16	out;
		ANTLR3_INT32    inSize;

		out = (pANTLR3_UINT16)(string->chars);
		inSize	= size;

		while	(inSize-- > 0)
		{
			*out++ = (ANTLR3_UINT16)(*ptr++);
		}


		*(((pANTLR3_UINT16)(string->chars)) + size) = '\0';

		string->len = size;
	}

	return  string;
}
