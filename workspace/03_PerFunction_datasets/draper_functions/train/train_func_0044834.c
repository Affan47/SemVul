binary_to_hex( unsigned char * bin, char * hex, int length )
{
	static const char trans[] = "0123456789ABCDEF";
	int i;

	for( i = 0; i < length; i++ )
	{
		hex[i<<1]     = trans[bin[i] >> 4];
		hex[(i<<1)+1] = trans[bin[i] & 0xf];
	}
	hex[i<<1] = '\0';
}
