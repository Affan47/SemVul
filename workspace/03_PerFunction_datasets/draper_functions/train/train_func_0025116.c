antlr3BitsetOf(ANTLR3_INT32 bit, ...)
{
    pANTLR3_BITSET  bitset;

    va_list ap;


    bitset  = antlr3BitsetNew(0);

    if	(bitset == NULL)
    {
		return	NULL;
    }


    va_start(ap, bit);
    while   (bit != -1)
    {
		antlr3BitsetAdd(bitset, bit);
		bit = va_arg(ap, ANTLR3_UINT32);
    }
    va_end(ap);


    return  bitset;
}
