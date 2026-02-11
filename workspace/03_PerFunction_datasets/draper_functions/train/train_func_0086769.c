doflush(struct base64decode *p)
{
	int i=p->workbuflen / 4;
	int j;
	int k=0;

	i= i * 4;

	for (j=0; j<i; j += 4)
	{
		char	a,b,c;

		int	w=p->workbuf[j];
		int	x=p->workbuf[j+1];
		int	y=p->workbuf[j+2];
		int	z=p->workbuf[j+3];

		a= (w << 2) | (x >> 4);
		b= (x << 4) | (y >> 2);
		c= (y << 6) | z;
		p->workbuf[k++]=a;
		if ( y != 100)
			p->workbuf[k++]=b;
		if ( z != 100)
			p->workbuf[k++]=c;
	}

	j= (*p->decode_func)(p->workbuf, k, p->decode_func_arg);

	k=0;
	while (i < p->workbuflen)
	{
		p->workbuf[k]=p->workbuf[i];
		++k;
		++i;
	}
	p->workbuflen=k;
	return (j);
}
