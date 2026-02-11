SHAtoByte(BYTE *output, UINT4 *input, unsigned int len)
{
	unsigned int i, j;

	for(i = 0, j = 0; j < len; i++, j += 4)
	{
        output[j+3] = (BYTE)( input[i]        & 0xff);
        output[j+2] = (BYTE)((input[i] >> 8 ) & 0xff);
        output[j+1] = (BYTE)((input[i] >> 16) & 0xff);
        output[j  ] = (BYTE)((input[i] >> 24) & 0xff);
	}
}
