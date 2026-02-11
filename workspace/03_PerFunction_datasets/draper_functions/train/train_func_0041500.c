from_utf8(struct charmap *map,unsigned char *s)
{
	int d = utf8_decode_string(s);
	int c = from_uni(map,d);
	if (c==-1)
		return '?';
	else
		return c;

#ifdef junk

	int ibuf_sz=zlen(s);
	unsigned char *ibufp=s;
	int obuf_sz=10;
	unsigned char obuf[10];
	unsigned char *obufp = obuf;


	if (from_utf==(iconv_t)-1 ||
	    iconv(from_utf,(char **)&ibufp,&ibuf_sz,(char **)&obufp,&obuf_sz)==((size_t)-1))
		return '?';
	else
		return obuf[0];
#endif
}
