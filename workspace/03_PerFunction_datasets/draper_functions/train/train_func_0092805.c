copy_to_pascal_two(char *dest, const char *src)
{
	unsigned short * sendlen = (void *) dest;
	char * data = dest + 2;

	unsigned short len ;
	if (!src) {
		dest[0]=0;
		dest[1]=0;
		return 2;
	}
	len = (unsigned short) strlen(src);
	*sendlen=htons(len);
	memcpy(data,src,len);
	return len;
}
