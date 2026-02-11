amessageV1(L9BYTE *ptr,int msg,long *w,long *c)
{
	int n;
	L9BYTE a;
	static int depth=0;

	while (msg--)
	{
		ptr+=msglenV1(&ptr);
	}
	if (ptr >= startdata+FileSize) return FALSE;
	n=msglenV1(&ptr);

	while (--n>0)
	{
		a=*ptr++;
		if (a<3) return TRUE;

		if (a>=0x5e)
		{
			if (++depth>10 || !amessageV1(startmdV2,a-0x5e,w,c))
			{
				depth--;
				return FALSE;
			}
			depth--;
		}
		else
		{
			char ch=a+0x1d;
			if (ch==0x5f || ch==' ') (*w)++;
			else (*c)++;
		}
	}
	return TRUE;
}
