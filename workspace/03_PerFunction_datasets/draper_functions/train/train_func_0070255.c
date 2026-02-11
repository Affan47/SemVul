append16_16	(pANTLR3_STRING string, const char * newbit)
{
    ANTLR3_UINT32 len;
    pANTLR3_UINT16  in;


    in	    = (pANTLR3_UINT16)newbit;
    len   = 0;

    while   (*in++ != '\0')
    {
		len++;
    }

    if	(string->size < (string->len + len + 1))
    {
		string->chars	= (pANTLR3_UINT8) ANTLR3_REALLOC((void *)string->chars, (ANTLR3_UINT32)( sizeof(ANTLR3_UINT16) *(string->len + len + 1) ));
		string->size	= string->len + len + 1;
    }


    ANTLR3_MEMMOVE((void *)(((pANTLR3_UINT16)string->chars) + string->len), newbit, (ANTLR3_UINT32)(sizeof(ANTLR3_UINT16)*(len+1)));
    string->len	+= len;

    return string->chars;
}
