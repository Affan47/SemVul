ftp_lite_parse_passive( const char *buffer, char *addr, int *port )
{
	int response, fields;
	int hi,lo;
	int a,b,c,d;

	fields = sscanf(buffer,"%d %*[^(] (%d,%d,%d,%d,%d,%d)",&response,&a,&b,&c,&d,&hi,&lo);
 	if(fields!=7) return 0;

	*port = hi*256+lo;
	sprintf(addr,"%d.%d.%d.%d",a,b,c,d);

	return 1;
}
