buf2hex(BYTE *bytes, INT len , CHAR *szStr)
{
	INT i;
	CHAR *oldstr;
	oldstr = szStr;
	for(i=0;i<len;i++,bytes++)
	{
		*szStr = int_to_hexchar((*bytes & 0xF0) / 0x10);
		szStr++;
		*szStr = int_to_hexchar(*bytes & 0xF);
		szStr++;


	}
	*szStr = 0;
	return oldstr;
}
