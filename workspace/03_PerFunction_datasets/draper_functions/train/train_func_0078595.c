SetEndian(void)
{
	union {qbyte b[2]; unsigned short s;} ed;
	ed.s = 255;
	if (ed.b[0] == 255)
	{
		PRBigShort		= QCC_SwapShort;
		PRLittleShort	= QCC_Short;
		PRBigLong		= QCC_SwapLong;
		PRLittleLong	= QCC_Long;
		PRBigFloat		= QCC_SwapFloat;
		PRLittleFloat	= QCC_Float;
	}
	else
	{
		PRBigShort		= QCC_Short;
		PRLittleShort	= QCC_SwapShort;
		PRBigLong		= QCC_Long;
		PRLittleLong	= QCC_SwapLong;
		PRBigFloat		= QCC_Float;
		PRLittleFloat	= QCC_SwapFloat;
	}
}
