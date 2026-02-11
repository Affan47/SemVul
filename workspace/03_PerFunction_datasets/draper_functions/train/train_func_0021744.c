new_string (char *s, unsigned long length, char *name)


{	unsigned long size;
	char *d;
	header *hd=(header *)newram;
	size=sizeof(header)+((int)(length+1)/ALIGNMENT+1)*ALIGNMENT;
	d=(char *)make_header(s_string,size,name);
	if (d) strncpy(d,s,length); d[length]=0;
	return hd;
}
