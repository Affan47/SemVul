bitswap(data8_t *src,size_t len,int _14,int _13,int _12,int _11,int _10,int _f,int _e,int _d,int _c,int _b,int _a,int _9,int _8,int _7,int _6,int _5,int _4,int _3,int _2,int _1,int _0)
{
	data8_t *buffer = malloc(len);

	if (buffer)
	{
		int i;

		memcpy(buffer,src,len);
		for (i = 0;i < len;i++)
		{
			src[i] =
				buffer[BITSWAP24(i,23,22,21,_14,_13,_12,_11,_10,_f,_e,_d,_c,_b,_a,_9,_8,_7,_6,_5,_4,_3,_2,_1,_0)];
		}
		free(buffer);
	}
}
