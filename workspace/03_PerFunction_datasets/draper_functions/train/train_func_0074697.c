dumpUDPData(fdInfoType *info,const void *ubuf,unsigned int len, const char *tag)
{
    register int i,j;
    register const unsigned char *buf=ubuf;
    static const char chars[]="0123456789abcdef";
    static int num=0;
    char out[2048];
    register char *p;

    num++;
    while (len) {
	sprintf(out,"%2s-%05x%c ",tag, num, (i ? '-' : ':'));
	p=out+10;
	i=256;
	while (len>0 && --i) {
	    *p++=chars[*buf>>4];
	    *p++=chars[*buf&15];
	    ++buf;
	    if (i%4==0) *p++=' ';
	    --len;
	}
	*p=0;
	syslog(LOG_DEBUG,"%s",out);
    }
}
