utf8_decode_string(unsigned char *s)
{
	struct utf8_sm sm;
	int x;
	int c = 0;
	utf8_init(&sm);
	for(x=0;s[x];++x)
		c = utf8_decode(&sm,s[x]);
	return c;
}
